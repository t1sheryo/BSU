import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { FirestoreService, Service } from '../../services/firestore.service';

@Component({
  selector: 'app-service-details',
  templateUrl: './service-details.component.html',
  styleUrls: ['./service-details.component.css']
})
export class ServiceDetailsComponent implements OnInit {
  service: Service | undefined;

  constructor(
    private route: ActivatedRoute,
    private firestoreService: FirestoreService
  ) { }

  ngOnInit() {
    this.route.params.subscribe(params => {
      const id = params['id'];
      this.firestoreService.getServiceById(id).subscribe(service => {
        this.service = service;
      });
    });
  }
}