<script setup lang="ts">
function returnRandomString() {
  return "/" + (Math.random() + 1).toString(36).substring(2);
}
</script>

<template>
  <header class="relative flex flex-wrap justify-between items-center px-2 py-4 bg-purple-800 mb-3 text-xl font-bold">
    <!-- LOGO -->
    <RouterLink to="/">
      <div id="logo" class="px-4 flex flex-wrap bg-purple-900 p-2 rounded-3xl ">
        <svg xmlns="http://www.w3.org/2000/svg" class="up-n-down icon icon-tabler icon-tabler-crystal-ball" width="32" height="32" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" fill="none" stroke-linecap="round" stroke-linejoin="round">
          <path stroke="none" d="M0 0h24v24H0z" fill="none"/>
          <path d="M6.73 17.018a8 8 0 1 1 10.54 0" />
          <path d="M5 19a2 2 0 0 0 2 2h10a2 2 0 1 0 0 -4h-10a2 2 0 0 0 -2 2z" />
          <path d="M11 7a3 3 0 0 0 -3 3" />
        </svg>
        Magična trgovina
      </div>
    </RouterLink>
    <!-- NAVIGATION -->
    <nav class="px-4 flex flex-wrap items-center gap-4 ">
      <RouterLink class="px-4 py-2 rounded-3xl bg-purple-900 " :to="returnRandomString()">Link na nasumičnu rutu</RouterLink>
      <RouterLink class="px-4 py-2 rounded-3xl bg-purple-900 " to="/cart">Košarica</RouterLink>
    </nav>

  </header>
</template>

<style scoped> 
/* scoped style */
.up-n-down {
  animation: up-n-down 1s linear 0s infinite forwards;
}

@keyframes up-n-down {
  0% {
    transform: translate(0px, 1px);
  }
  25% {
    transform: translate(1px, 0px);
  }
  50% {
    transform: translate(0px, -1px);
  }
  75% {
    transform: translate(-1px, 0px);
  }
  100% {
    transform: translate(0px, 1px);
  }
}
</style>