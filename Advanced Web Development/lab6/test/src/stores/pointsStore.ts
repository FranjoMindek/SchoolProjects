import { defineStore } from "pinia";
import { ref } from "vue";

export const usePointsStore = defineStore("pointsStore", () => {
  const points = ref(425);

  function spend(price: number) {
    points.value -= price;
  }

  return {points, spend};
});