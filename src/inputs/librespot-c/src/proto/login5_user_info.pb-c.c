/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: login5_user_info.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "login5_user_info.pb-c.h"
void   spotify__login5__v3__user_info__init
                     (Spotify__Login5__V3__UserInfo         *message)
{
  static const Spotify__Login5__V3__UserInfo init_value = SPOTIFY__LOGIN5__V3__USER_INFO__INIT;
  *message = init_value;
}
size_t spotify__login5__v3__user_info__get_packed_size
                     (const Spotify__Login5__V3__UserInfo *message)
{
  assert(message->base.descriptor == &spotify__login5__v3__user_info__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t spotify__login5__v3__user_info__pack
                     (const Spotify__Login5__V3__UserInfo *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &spotify__login5__v3__user_info__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t spotify__login5__v3__user_info__pack_to_buffer
                     (const Spotify__Login5__V3__UserInfo *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &spotify__login5__v3__user_info__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Spotify__Login5__V3__UserInfo *
       spotify__login5__v3__user_info__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Spotify__Login5__V3__UserInfo *)
     protobuf_c_message_unpack (&spotify__login5__v3__user_info__descriptor,
                                allocator, len, data);
}
void   spotify__login5__v3__user_info__free_unpacked
                     (Spotify__Login5__V3__UserInfo *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &spotify__login5__v3__user_info__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCEnumValue spotify__login5__v3__user_info__gender__enum_values_by_number[4] =
{
  { "UNKNOWN", "SPOTIFY__LOGIN5__V3__USER_INFO__GENDER__UNKNOWN", 0 },
  { "MALE", "SPOTIFY__LOGIN5__V3__USER_INFO__GENDER__MALE", 1 },
  { "FEMALE", "SPOTIFY__LOGIN5__V3__USER_INFO__GENDER__FEMALE", 2 },
  { "NEUTRAL", "SPOTIFY__LOGIN5__V3__USER_INFO__GENDER__NEUTRAL", 3 },
};
static const ProtobufCIntRange spotify__login5__v3__user_info__gender__value_ranges[] = {
{0, 0},{0, 4}
};
static const ProtobufCEnumValueIndex spotify__login5__v3__user_info__gender__enum_values_by_name[4] =
{
  { "FEMALE", 2 },
  { "MALE", 1 },
  { "NEUTRAL", 3 },
  { "UNKNOWN", 0 },
};
const ProtobufCEnumDescriptor spotify__login5__v3__user_info__gender__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "spotify.login5.v3.UserInfo.Gender",
  "Gender",
  "Spotify__Login5__V3__UserInfo__Gender",
  "spotify.login5.v3",
  4,
  spotify__login5__v3__user_info__gender__enum_values_by_number,
  4,
  spotify__login5__v3__user_info__gender__enum_values_by_name,
  1,
  spotify__login5__v3__user_info__gender__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor spotify__login5__v3__user_info__field_descriptors[8] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "email",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, email),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "email_verified",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, email_verified),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "birthdate",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, birthdate),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "gender",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, gender),
    &spotify__login5__v3__user_info__gender__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "phone_number",
    6,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, phone_number),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "phone_number_verified",
    7,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, phone_number_verified),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "email_already_registered",
    8,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BOOL,
    0,   /* quantifier_offset */
    offsetof(Spotify__Login5__V3__UserInfo, email_already_registered),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned spotify__login5__v3__user_info__field_indices_by_name[] = {
  3,   /* field[3] = birthdate */
  1,   /* field[1] = email */
  7,   /* field[7] = email_already_registered */
  2,   /* field[2] = email_verified */
  4,   /* field[4] = gender */
  0,   /* field[0] = name */
  5,   /* field[5] = phone_number */
  6,   /* field[6] = phone_number_verified */
};
static const ProtobufCIntRange spotify__login5__v3__user_info__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor spotify__login5__v3__user_info__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "spotify.login5.v3.UserInfo",
  "UserInfo",
  "Spotify__Login5__V3__UserInfo",
  "spotify.login5.v3",
  sizeof(Spotify__Login5__V3__UserInfo),
  8,
  spotify__login5__v3__user_info__field_descriptors,
  spotify__login5__v3__user_info__field_indices_by_name,
  1,  spotify__login5__v3__user_info__number_ranges,
  (ProtobufCMessageInit) spotify__login5__v3__user_info__init,
  NULL,NULL,NULL    /* reserved[123] */
};
