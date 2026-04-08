import { ApplicationConfig, provideBrowserGlobalErrorListeners, provideZonelessChangeDetection } from '@angular/core';
import { provideRouter } from '@angular/router';
 import { provideHttpClient } from '@angular/common/http';

import { routes } from './app.routes';
import { provideClientHydration, withEventReplay } from '@angular/platform-browser';
import { provideFirebaseApp, initializeApp } from '@angular/fire/app';
import { provideFirestore, getFirestore } from '@angular/fire/firestore';
// Используем прямой объект конфигурации, чтобы избежать проблем с импортацией environments
const firebaseConfig = {
  apiKey: "AIzaSyD7INsAx8imW3M3LNgmRPBIADU47F3727Q",
  authDomain: "lab2-b6223.firebaseapp.com",
  projectId: "lab2-b6223",
  storageBucket: "lab2-b6223.firebasestorage.app",
  messagingSenderId: "119275606181",
  appId: "1:119275606181:web:88ca40c367e0807ece7d4c"
};

export const appConfig: ApplicationConfig = {
  providers: [
    provideBrowserGlobalErrorListeners(),
    provideZonelessChangeDetection(),
    provideRouter(routes), provideClientHydration(withEventReplay()),
    provideHttpClient(),
    provideFirebaseApp(() => initializeApp(firebaseConfig as any)),
    provideFirestore(() => getFirestore())
  ]
};
