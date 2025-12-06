import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';
import { FirestoreService, Service } from '../../services/firestore.service';
import { Observable } from 'rxjs';

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
    private firestoreService: FirestoreService
  ) {
    this.services$ = this.firestoreService.getServices();
  }

  ngOnInit() { }

  selectService(service: Service) {
    this.router.navigate(['/services', service.id]);
  }
}