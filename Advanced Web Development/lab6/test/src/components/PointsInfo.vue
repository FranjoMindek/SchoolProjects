<script setup lang="ts">
import { usePointsStore } from '@/stores/pointsStore';
import { computed } from 'vue';
const props = defineProps<{ // glupa komponenta koristi samo props
  points: number
}>();
const inDebt = computed(() => props.points < 0); //computed properties

</script>

<template>
  <div class="px-4 py-4 bg-amber-600 font-semibold flex flex-col items-center border-t-8 border-x-[5px] rounded-t-3xl w-72 text-center" 
    :class="{' border-green-600': !inDebt, ' border-red-600': inDebt}">
    <div class="text-xl">
      Preostalo bodova: {{ points }}
    </div>
    <div v-if="!inDebt"> 
      Vaša duša je sigurna...zasada.. :)
    </div>
    <div v-else>
      Prelaskom u dug prodali ste pravo na vlastitu dušu! :(
    </div>
  </div>
</template>
