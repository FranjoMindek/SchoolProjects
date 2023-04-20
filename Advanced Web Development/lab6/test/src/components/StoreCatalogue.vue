<script setup lang="ts">
import { db } from '@/firebase';
import type { StoreItem } from '@/models/StoreItem';
import { useItemsStore } from '@/stores/itemsStore';
import { usePointsStore } from '@/stores/pointsStore';
import { collection, getDocs, QuerySnapshot, type DocumentData } from 'firebase/firestore';
import { computed, onBeforeMount, reactive, ref } from 'vue';
import StoreItemCard from './StoreItemCard.vue';
import PointsInfo from './PointsInfo.vue';

const storeItems: StoreItem[] = reactive([]);
const offer = ref(""); //two-way binding -> koristi v-model dolje
const isOfferTouched = ref(false);
const loading = computed(() => storeItems.length === 0);
const offerAcceptedComputed = computed(() => { return offer.value.toLowerCase() === "Pristajem na sve uvjete".toLowerCase() });
const offerAccepted = ref(false); 

const itemsStore = useItemsStore();
const pointsStore = usePointsStore();

function getItems() { // metoda
  const storeItemsRef = collection(db, 'storeItems');
  getDocs(storeItemsRef)  //asinkroni dohvat
  .then((items: QuerySnapshot<DocumentData>) => {
    items.forEach((item) => {
      storeItems.push(item.data() as StoreItem);
    });
  });
};

onBeforeMount(() => { //lifecycyle hook
  if (sessionStorage.getItem("offer") === "accepted") {
    offerAccepted.value = true;
  }
  getItems();
});

function checkOffer() { // metoda
  if(offerAcceptedComputed.value) {
    sessionStorage.setItem("offer", "accepted");
  } 
}

function offerTouched() {
  isOfferTouched.value = true;
}

</script>

<template>
  <div v-if="!(offerAccepted || offerAcceptedComputed)" class="flex flex-col items-center py-10 text-black text-xl relative">
    <input v-model="offer" 
      placeholder="Napišite: 'Pristajem na sve uvjete' da bi ste nastavili!"
      class="w-[50vw]"
      @input="checkOffer()"
      @focusin="offerTouched()"
      />
    <div v-if="isOfferTouched" class="italic text-white text-base">
      Napišite: 'Pristajem na sve uvjete' da bi ste nastavili!
    </div>
  </div>
  <div v-else>
    <div class="relative py-10 flex flex-col items-center">
      <div class="text-xl text-center p-10 border-2 border-amber-500 mb-10 w-fit">
        Birajte svoje predmete mudro jer imate budžet od samo 425 čarobnih novčanica. <br/>
        Zapamtite, vaša odluka je konačna.
      </div>
      <div v-if="!loading">
        <ul class="flex flex-row flex-wrap justify-center gap-4">
          <li v-for="item in storeItems" :key="item.title" class="basis-1/6">
            <StoreItemCard :storeItem="item" @bought="(storeItem: StoreItem) => {
              itemsStore.addItem(storeItem);
              pointsStore.spend(storeItem.price);
            }">
              <template #icon>
                Temp
              </template>
            </StoreItemCard>
          </li>
        </ul>
        <div class="smoke absolute bottom-0 left-0 w-44 h-96"></div>
        <div class="smoke absolute bottom-0 right-0 w-44 h-96"></div>
      </div>
      <div v-else class="text-3xl italic">
        Drevna magija učitava trgovinu
      </div>
    </div>

    <PointsInfo class="fixed bottom-0 right-[10vw]" :points="pointsStore.points"/>
  </div>
</template>