<template>
  <modal-dialog
    :actions="actions"
    :show="show"
    :title="$t('dialog.add.stream.title')"
    @close="$emit('close')"
  >
    <template #content>
      <form @submit.prevent="play">
        <control-url-field
          icon="web"
          :loading="loading"
          :placeholder="$t('dialog.add.stream.placeholder')"
          @input="onUrlChange"
        />
      </form>
    </template>
  </modal-dialog>
</template>

<script>
import ControlUrlField from '@/components/ControlUrlField.vue'
import ModalDialog from '@/components/ModalDialog.vue'
import queue from '@/api/queue'

export default {
  name: 'ModalDialogAddStream',
  components: { ControlUrlField, ModalDialog },
  props: { show: Boolean },
  emits: ['close'],
  data() {
    return {
      disabled: true,
      loading: false,
      url: ''
    }
  },
  computed: {
    actions() {
      if (this.loading) {
        return [{ icon: 'web', key: 'dialog.add.stream.processing' }]
      }
      return [
        { handler: this.cancel, icon: 'cancel', key: 'actions.cancel' },
        {
          disabled: this.disabled,
          handler: this.add,
          icon: 'playlist-plus',
          key: 'actions.add'
        },
        {
          disabled: this.disabled,
          handler: this.play,
          icon: 'play',
          key: 'actions.play'
        }
      ]
    }
  },
  methods: {
    add() {
      this.loading = true
      queue
        .addUri(this.url)
        .then(() => {
          this.$emit('close')
        })
        .finally(() => {
          this.url = ''
          this.loading = false
        })
    },
    cancel() {
      this.$emit('close')
    },
    onUrlChange(url, disabled) {
      this.url = url
      this.disabled = disabled
    },
    play() {
      this.loading = true
      queue
        .playUri(this.url, false)
        .then(() => {
          this.$emit('close')
          this.url = ''
        })
        .catch(() => {
          this.loading = false
        })
    }
  }
}
</script>
