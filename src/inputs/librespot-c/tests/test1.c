#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

// For file output
#include <sys/stat.h>
#include <fcntl.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <curl/curl.h>

#include "librespot-c.h"

static int audio_fd = -1;
static int test_file = -1;
static struct event_base *evbase;
static struct evbuffer *audio_buf;

static int total_bytes;

#include <ctype.h> // for isprint()

static void
hexdump_dummy(const char *msg, uint8_t *mem, size_t len)
{
  return;
}

static void
hexdump(const char *msg, uint8_t *mem, size_t len)
{
  int i, j;
  int hexdump_cols = 16;

  if (msg)
    printf("%s", msg);

  for (i = 0; i < len + ((len % hexdump_cols) ? (hexdump_cols - len % hexdump_cols) : 0); i++)
    {
      if(i % hexdump_cols == 0)
	printf("0x%06x: ", i);

      if (i < len)
	printf("%02x ", 0xFF & ((char*)mem)[i]);
      else
	printf("   ");

      if (i % hexdump_cols == (hexdump_cols - 1))
	{
	  for (j = i - (hexdump_cols - 1); j <= i; j++)
	    {
	      if (j >= len)
		putchar(' ');
	      else if (isprint(((char*)mem)[j]))
		putchar(0xFF & ((char*)mem)[j]);
	      else
		putchar('.');
	    }

	  putchar('\n');
	}
    }
}

static void
logmsg(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
}

static int
tcp_connect(const char *address, unsigned short port)
{
  struct addrinfo hints = { 0 };
  struct addrinfo *servinfo;
  struct addrinfo *ptr;
  char strport[8];
  int fd;
  int ret;

  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_UNSPEC;

  snprintf(strport, sizeof(strport), "%hu", port);
  ret = getaddrinfo(address, strport, &hints, &servinfo);
  if (ret < 0)
    {
      printf("Could not connect to %s (port %u): %s\n", address, port, gai_strerror(ret));
      return -1;
    }

  for (ptr = servinfo; ptr; ptr = ptr->ai_next)
    {
      fd = socket(ptr->ai_family, SOCK_STREAM, ptr->ai_protocol);
      if (fd < 0)
	{
	  continue;
	}

      ret = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
      if (ret < 0)
	{
	  close(fd);
	  continue;
	}

      break;
    }

  freeaddrinfo(servinfo);

  if (!ptr)
    {
      printf("Could not connect to '%s' (port %u): %s\n", address, port, strerror(errno));
      return -1;
    }

  printf("Connected to %s (port %u)\n", address, port);

  return fd;
}

static void
tcp_disconnect(int fd)
{
  if (fd < 0)
    return;

  close(fd);
}

static void
progress_cb(int fd, void *arg, size_t received, size_t len)
{
  printf("Progress on fd %d is %zu/%zu\n", fd, received, len);
}

// This thread
static void
audio_read_cb(int fd, short what, void *arg)
{
  int got;

  got = evbuffer_read(audio_buf, fd, -1);
  if (got <= 0)
    {
      printf("Playback ended (%d)\n", got);
      event_base_loopbreak(evbase);
      return;
    }

  total_bytes += got;

  printf("Got %d bytes of audio, total received is %d bytes\n", got, total_bytes);

  evbuffer_write(audio_buf, test_file);
}

struct sp_callbacks callbacks =
{
  .tcp_connect = tcp_connect,
  .tcp_disconnect = tcp_disconnect,

  .thread_name_set = NULL,

  .hexdump  = hexdump,
  .logmsg   = logmsg,
};

int
main(int argc, char * argv[])
{
  struct sp_session *session = NULL;
  struct sp_sysinfo sysinfo;
  struct sp_credentials credentials;
  struct sp_metadata metadata;
  struct event *read_ev;
  uint8_t stored_cred[256];
  size_t stored_cred_len;
//  struct event *stop_ev;
//  struct timeval tv = { 0 };
  int ret;

  if (argc != 4)
    {
      printf("%s spotify_path username access_token\n", argv[0]);
      goto error;
    }

  memset(&sysinfo, 0, sizeof(struct sp_sysinfo));
  snprintf(sysinfo.device_id, sizeof(sysinfo.device_id), "aabbccddeeff");

  ret = librespotc_init(&sysinfo, &callbacks);
  if (ret < 0)
    {
      printf("Error initializing Spotify: %s\n", librespotc_last_errmsg());
      goto error;
    }

  session = librespotc_login_token(argv[2], argv[3]);
  if (!session)
    {
      printf("Error logging in with token: %s\n", librespotc_last_errmsg());
      goto error;
    }

  printf("\n--- Login with token OK ---\n\n");

  ret = librespotc_credentials_get(&credentials, session);
  if (ret < 0)
    {
      printf("Error getting session credentials: %s\n", librespotc_last_errmsg());
      goto error;
    }

  printf("=== CREDENTIALS ===\n");
  printf("Username:\n%s\n", credentials.username);
  hexdump("Stored credentials:\n", credentials.stored_cred, credentials.stored_cred_len);
  printf("===================\n");

  // "Store" the credentials
  stored_cred_len = credentials.stored_cred_len;
  if (stored_cred_len > sizeof(stored_cred))
    {
      printf("Unexpected length of stored credentials\n");
      goto error;
    }
  memcpy(stored_cred, credentials.stored_cred, stored_cred_len);

  librespotc_logout(session);

  session = librespotc_login_stored_cred(argv[2], stored_cred, stored_cred_len);
  if (!session)
    {
      printf("Error logging in with stored credentials: %s\n", librespotc_last_errmsg());
      goto error;
    }

  printf("\n--- Login with stored credentials OK ---\n\n");

  audio_fd = librespotc_open(argv[1], session);
  if (audio_fd < 0)
    {
      printf("Error opening file: %s\n", librespotc_last_errmsg());
      goto error;
    }

  ret = librespotc_metadata_get(&metadata, audio_fd);
  if (ret < 0)
    {
      printf("Error getting track metadata: %s\n", librespotc_last_errmsg());
      goto error;
    }

  printf("File is open, length is %zu\n", metadata.file_len);

  ret = librespotc_seek(audio_fd, 1000000);
  if (ret < 0)
    {
      printf("Error seeking: %s\n", librespotc_last_errmsg());
      goto error;
    }

  test_file = open("testfile.ogg", O_CREAT | O_RDWR, 0664);
  if (test_file < 0)
    {
      printf("Error opening testfile.ogg: %s\n", strerror(errno));
      goto error;
    }

  evbase = event_base_new();
  audio_buf = evbuffer_new();

  read_ev = event_new(evbase, audio_fd, EV_READ | EV_PERSIST, audio_read_cb, NULL);
  event_add(read_ev, NULL);

  librespotc_write(audio_fd, progress_cb, NULL);

//  stop_ev = evtimer_new(evbase, stop, &audio_fd);
//  tv.tv_sec = 2;
//  event_add(stop_ev, &tv);

  event_base_dispatch(evbase);

//  event_free(stop_ev);
  event_free(read_ev);

  close(test_file);

  evbuffer_free(audio_buf);

  event_base_free(evbase);

  librespotc_close(audio_fd);

  librespotc_logout(session);

  librespotc_deinit();

  return 0;

 error:
  if (test_file >= 0)
    close(test_file);
  if (audio_fd >= 0)
    librespotc_close(audio_fd);
  if (session)
    librespotc_logout(session);

  librespotc_deinit();

  return -1;
}
