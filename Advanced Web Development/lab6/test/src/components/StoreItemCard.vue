<script setup lang="ts">
import type { StoreItem } from '@/models/StoreItem';
import { usePointsStore } from '@/stores/pointsStore';
const pointsStore = usePointsStore();
const props = defineProps<{ // glupa komponenta koristi samo props i store
  storeItem: StoreItem
}>();
</script>

<template>
  <div class="flex flex-col items-center border-[3px] border-amber-500 p-3 text-center">
    <!-- SLIKA -->
    <div class="bg-white rounded-full p-2 border-[6px] border-purple-700">
      <img
        :src="'./' + storeItem.svg"
        class="w-32 h-32"
      />
    </div>
    <!-- NAZIV -->
    <div>
      <h1 class="text-2xl italic">
        {{ storeItem.title }}
      </h1>
    </div>
    <!-- CIJENA -->
    <div >
      <h2 class="text-amber-500">
        {{ storeItem.price + ' novaca' }}
      </h2>
    </div>
    <!-- OPIS -->
    <div class="my-4">
      <h3 class="text-zinc-200 ">
        {{ storeItem.description }}
      </h3>
    </div>
    <!-- BUTTON - emitira event -->
    <button class="px-4 py-2 bg-amber-600 rounded-3xl font-bold" 
      @click="$emit('bought', storeItem)" 
      :disabled="pointsStore.points < 0">
      Kupi me
    </button>
    
  </div>
</template>
