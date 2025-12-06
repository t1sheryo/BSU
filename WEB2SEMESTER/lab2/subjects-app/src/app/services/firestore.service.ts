import { Injectable } from '@angular/core';
import { 
  Firestore, 
  collection, 
  collectionData, 
  doc, 
  addDoc, 
  updateDoc, 
  deleteDoc,
  getDoc 
} from '@angular/fire/firestore';
import { Observable } from 'rxjs';

export interface Service {
  id?: string;  // Теперь string, так как Firestore использует string ID
  description: string;
  price: number;
}

@Injectable({
  providedIn: 'root'
})
export class FirestoreService {
  constructor(private firestore: Firestore) { }

  // Получить все сервисы
  getServices(): Observable<Service[]> {
    const servicesRef = collection(this.firestore, 'services'); // коллекция 'services'
    return collectionData(servicesRef, { idField: 'id' }) as Observable<Service[]>;
  }

  // Получить сервис по ID
  getServiceById(id: string): Observable<Service | undefined> {
    return new Observable(observer => {
      const serviceDoc = doc(this.firestore, `services/${id}`);
      getDoc(serviceDoc).then(docSnapshot => {
        if (docSnapshot.exists()) {
          observer.next({ id: docSnapshot.id, ...docSnapshot.data() } as Service);
        } else {
          observer.next(undefined);
        }
        observer.complete();
      });
    });
  }

  // Добавить сервис
  addService(service: Service) {
    const servicesRef = collection(this.firestore, 'services');
    return addDoc(servicesRef, service);
  }

  // Обновить сервис
  updateService(id: string, service: Partial<Service>) {
    const serviceDocRef = doc(this.firestore, `services/${id}`);
    return updateDoc(serviceDocRef, service);
  }

  // Удалить сервис
  deleteService(id: string) {
    const serviceDocRef = doc(this.firestore, `services/${id}`);
    return deleteDoc(serviceDocRef);
  }
}