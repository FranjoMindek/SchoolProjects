<script setup lang="ts">
import { RouterView } from "vue-router";
import Header from "./components/core/Header.vue";
</script>

<template>
  <div class="text-white bg-purple-900 min-h-screen relative">
    <Header></Header>
    <div class="mx-6">
      <RouterView/>
    </div>
  </div>
</template>