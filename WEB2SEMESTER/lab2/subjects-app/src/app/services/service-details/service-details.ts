import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ActivatedRoute } from '@angular/router';
import { ServiceApiService, Service } from '../service';

@Component({
  selector: 'app-service-details',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './service-details.component.html',
  styleUrls: ['./service-details.component.css']
})
export class ServiceDetailsComponent implements OnInit {

  service: Service | undefined;

  constructor(
    private route: ActivatedRoute,
    private serviceApi: ServiceApiService
  ) { }

  ngOnInit() {
    this.route.params.subscribe(params => {
      const id = Number(params['id']);
      this.serviceApi.getById(id).subscribe({
        next: service => {
          this.service = service;
        },
        error: err => {
          console.error('Failed to load service details via HTTP:', err);
          this.service = undefined;
        }
      });
    });
  }
}