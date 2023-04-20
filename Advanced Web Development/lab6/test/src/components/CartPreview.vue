<script setup lang="ts">
import { useItemsStore } from '@/stores/itemsStore';
import CartItemCard from './CartItemCard.vue';

const itemsStore = useItemsStore();

</script>

<template >
  <div class="relative" v-if="itemsStore.items.length > 0">
    <ul class="flex flex-row flex-wrap justify-center gap-4">
      <li v-for="item in itemsStore.items" :key="item.title" class="basis-1/6">
        <CartItemCard :storeItem="item">
        </CartItemCard>
      </li>
    </ul>

    <div class="smoke absolute bottom-0 left-0 w-44 h-96"></div>
    <div class="smoke absolute bottom-0 right-0 w-44 h-96"></div>

  </div>
</template>
