<script setup lang="ts">
</script>

<template>
  <div class="flex flex-col justify-between ">
    <div class="big-title text-center border-amber-500 border-4 bg-purple-800 my-12 mx-32">
      Nažalost ne možemo pronaći strnaicu koju želite.
    </div>

    <div class="flex justify-between mt-10">
      <div class="smoke w-44 h-96"></div>
      <div class="smoke w-44 h-96"></div>
      <div class="smoke w-44 h-96"></div>
      <div class="smoke w-44 h-96"></div>
      <div class="smoke w-44 h-96"></div>
    </div>
    
  </div>
</template>

<style scoped>
.big-title{
  font-size: 100px;
  animation: shake 2s ease-in-out 0s infinite alternate-reverse;
}

@keyframes shake {
  0% {
    transform: translateY(20px)
  }
  100% {
    transform: translateY(-20px)
  }
}
</style>
