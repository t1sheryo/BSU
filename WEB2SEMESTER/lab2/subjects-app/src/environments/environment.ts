// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyD7INsAx8imW3M3LNgmRPBIADU47F3727Q",
  authDomain: "lab2-b6223.firebaseapp.com",
  projectId: "lab2-b6223",
  storageBucket: "lab2-b6223.firebasestorage.app",
  messagingSenderId: "119275606181",
  appId: "1:119275606181:web:88ca40c367e0807ece7d4c",
  measurementId: "G-5T7VVSFH0N"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);