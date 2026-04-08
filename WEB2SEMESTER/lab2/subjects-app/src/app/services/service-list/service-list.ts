import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';
import { ServiceApiService, Service } from '../service';
import { Observable, catchError, of } from 'rxjs';

@Component({
  selector: 'app-service-list',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './service-list.component.html',
  styleUrls: ['./service-list.component.css']
})
export class ServiceListComponent implements OnInit {
  services$: Observable<Service[]>;

  constructor(
    private router: Router,
    private serviceApi: ServiceApiService
  ) {
    this.services$ = this.serviceApi.getAll().pipe(
      catchError(err => {
        console.error('Failed to load services via HTTP:', err);
        return of([]);
      })
    );
  }

  ngOnInit() { }

  selectService(service: Service) {
    this.router.navigate(['/services', service.id]);
  }
}