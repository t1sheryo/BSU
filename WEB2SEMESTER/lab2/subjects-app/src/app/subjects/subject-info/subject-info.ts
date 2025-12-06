import { Component } from '@angular/core';
import { NgIf } from '@angular/common';
import { ActivatedRoute, Router, RouterLink } from '@angular/router';
import { SubjectService } from '../services/subject.service';
import { Subject } from '../subject';

@Component({
  selector: 'app-subject-info',
  imports: [RouterLink, NgIf],
  template: `
    <div class="card" *ngIf="subject as s">
      <div class="card-body">
        <h5 class="card-title">{{ s.name }}</h5>
        <p class="mb-1"><strong>Преподаватель:</strong> {{ s.teacher }}</p>
        <p class="mb-3"><strong>Кредиты:</strong> {{ s.credits }}</p>
        <p class="mb-3">{{ s.description }}</p>
        <div class="d-flex gap-2">
          <a class="btn btn-primary" [routerLink]="['/subjects','edit', s.id]">Редактировать</a>
          <button class="btn btn-danger" (click)="delete()">Удалить</button>
          <a class="btn btn-secondary" [routerLink]="['/subjects']">Назад</a>
        </div>
      </div>
    </div>
  `,
  styles: ``
})
export class SubjectInfo {
  subject?: Subject;

  constructor(private route: ActivatedRoute, private router: Router, private svc: SubjectService) {
    const id = Number(this.route.snapshot.paramMap.get('id'));
    this.subject = this.svc.getById(id);
  }

  delete() {
    if (this.subject?.id) {
      this.svc.remove(this.subject.id);
      this.router.navigate(['/subjects']);
    }
  }
}
