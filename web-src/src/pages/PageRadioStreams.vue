<template>
  <content-with-heading>
    <template #options>
      <list-index-buttons :indices="tracks.indices" />
    </template>
    <template #heading>
      <pane-title :content="heading" />
    </template>
    <template #content>
      <list-tracks :items="tracks" />
    </template>
  </content-with-heading>
</template>

<script>
import ContentWithHeading from '@/templates/ContentWithHeading.vue'
import { GroupedList } from '@/lib/GroupedList'
import ListIndexButtons from '@/components/ListIndexButtons.vue'
import ListTracks from '@/components/ListTracks.vue'
import PaneTitle from '@/components/PaneTitle.vue'
import library from '@/api/library'

export default {
  name: 'PageRadioStreams',
  components: {
    ContentWithHeading,
    ListIndexButtons,
    ListTracks,
    PaneTitle
  },
  beforeRouteEnter(to, from, next) {
    library.radioStreams().then((tracks) => {
      next((vm) => {
        vm.tracks = new GroupedList(tracks, {
          index: { field: 'title_sort', type: String }
        })
      })
    })
  },
  data() {
    return {
      tracks: new GroupedList()
    }
  },
  computed: {
    heading() {
      return {
        subtitle: [{ count: this.tracks.total, key: 'data.stations' }],
        title: this.$t('page.radio.title')
      }
    }
  }
}
</script>
