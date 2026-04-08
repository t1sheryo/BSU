 import { Injectable } from '@angular/core';
 import { HttpClient, HttpHeaders } from '@angular/common/http';
 import { Observable } from 'rxjs';

export interface Service {
  id: number;
  description: string;
  price: number;
}

@Injectable({
  providedIn: 'root'
})
export class ServiceApiService {

  serviceUrl = 'http://localhost:8080/api/services';

  private readonly jsonHeaders = new HttpHeaders({
    'Content-Type': 'application/json'
  });

  constructor(private httpClient: HttpClient) {
  }

  getAll(): Observable<Service[]> {
    return this.httpClient.get<Service[]>(this.serviceUrl);
  }

  getById(id: number): Observable<Service> {
    return this.httpClient.get<Service>(`${this.serviceUrl}/${id}`);
  }

  add(service: Omit<Service, 'id'>): Observable<Service> {
    return this.httpClient.post<Service>(this.serviceUrl, service, { headers: this.jsonHeaders });
  }

  remove(id: number): Observable<void> {
    return this.httpClient.delete<void>(`${this.serviceUrl}/${id}`);
  }
}
