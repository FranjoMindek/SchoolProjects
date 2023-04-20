<script setup lang="ts">
import type { StoreItem } from '@/models/StoreItem';
const props = defineProps<{ // glupa komponenta koristi samo props
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
    
  </div>
</template>

<style scoped>
</style>
