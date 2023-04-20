import { createRouter, createWebHistory } from "vue-router";
import StoreView from "../views/StoreView.vue";
import NotFound from "../views/NotFound.vue";
import CartView from "../views/CartView.vue";

// 2 rute + 1 wildcard ruta za 404
const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: "/",
      name: "home",
      component: StoreView,
    },
    {
      path: "/cart",
      name: "cart",
      component: CartView,
    },
    {
      path: '/:pathMatch(.*)*', 
      name: 'NotFound', 
      component: NotFound, 
    }
  ],
});

export default router;
