import type { StoreItem } from "@/models/StoreItem";
import { defineStore } from "pinia";
import { reactive } from "vue";

export const useItemsStore = defineStore("itemsStore", () => {
  const items: StoreItem[] = reactive([]);

  function addItem(item: StoreItem) {
    items.push(item);
  }

  return {items, addItem};
});