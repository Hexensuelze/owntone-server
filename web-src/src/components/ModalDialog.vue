<template>
  <transition name="fade">
    <div v-if="show" class="modal is-active">
      <div class="modal-background" @click="$emit('close')" />
      <div class="modal-content">
        <div class="card is-shadowless">
          <div class="card-header">
            <div v-if="title" class="card-header-title" v-text="title" />
            <div class="card-header-icon">
              <button class="delete" @click="$emit('close')"></button>
            </div>
          </div>
          <div class="card-content">
            <slot name="content" />
          </div>
          <footer v-if="actions.length" class="card-footer">
            <button
              v-for="action in actions"
              :key="action.key"
              class="card-footer-item is-small"
              :class="{ 'is-disabled': action.disabled }"
              :disabled="action.disabled"
              @click="action.handler"
            >
              <mdicon class="icon" :name="action.icon" size="16" />
              <span class="is-size-7" v-text="$t(action.key)" />
            </button>
          </footer>
        </div>
      </div>
    </div>
  </transition>
</template>

<script>
export default {
  name: 'ModalDialog',
  props: {
    actions: { required: true, type: Array },
    show: Boolean,
    title: { default: '', type: String }
  },
  emits: ['close'],
  watch: {
    show(value) {
      const { classList } = document.querySelector('html')
      if (value) {
        classList.add('is-clipped')
      } else {
        classList.remove('is-clipped')
      }
    }
  }
}
</script>

<style scoped>
.card-content {
  max-height: calc(100vh - calc(4 * var(--bulma-navbar-height)));
  overflow: auto;
}
.fade-leave-active {
  transition: opacity 0.2s ease;
}
.fade-enter-active {
  transition: opacity 0.5s ease;
}
.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}
.fade-enter-to,
.fade-leave-from {
  opacity: 1;
}
.is-disabled {
  cursor: not-allowed;
  opacity: 0.5;
  > * {
    pointer-events: none;
  }
}
.modal-background {
  background-color: rgba(10, 10, 10, 0.5);
}
</style>
