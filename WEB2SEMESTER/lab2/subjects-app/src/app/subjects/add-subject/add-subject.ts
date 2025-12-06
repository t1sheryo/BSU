import { Component } from '@angular/core';
import { FormsModule, NgForm } from '@angular/forms';
import { NgIf } from '@angular/common';
import { Router, ActivatedRoute } from '@angular/router';
import { Subject } from '../subject';
import { SubjectService } from '../services/subject.service';

@Component({
  selector: 'app-add-subject',
  imports: [FormsModule, NgIf],
  template: `
    <div class="card">
      <div class="card-body">
        <h5 class="card-title">{{ isEdit ? 'Редактировать предмет' : 'Добавить предмет' }}</h5>
        <form #f="ngForm" (ngSubmit)="onSubmit(f)">
          <div class="mb-3">
            <label class="form-label">Название</label>
            <input class="form-control" name="name" [(ngModel)]="model.name" required />
          </div>
          <div class="mb-3">
            <label class="form-label">Преподаватель</label>
            <input class="form-control" name="teacher" [(ngModel)]="model.teacher" required />
          </div>
          <div class="mb-3">
            <label class="form-label">Кредиты</label>
            <input type="number" class="form-control" name="credits" [(ngModel)]="model.credits" required min="1" />
          </div>
          <div class="mb-3">
            <label class="form-label">Описание</label>
            <textarea class="form-control" name="description" [(ngModel)]="model.description"></textarea>
          </div>
          <div class="d-flex gap-2">
            <button class="btn btn-primary" type="submit" [disabled]="f.invalid">{{ isEdit ? 'Сохранить' : 'Добавить' }}</button>
            <button *ngIf="isEdit" type="button" class="btn btn-danger" (click)="onDelete()">Удалить</button>
            <button type="button" class="btn btn-secondary" (click)="goBack()">Отмена</button>
          </div>
        </form>
      </div>
    </div>
  `,
  styles: ``
})
export class AddSubject {
  isEdit = false;
  model: Subject = { id: 0, name: '', teacher: '', credits: 1, description: '' };

  constructor(private svc: SubjectService, private router: Router, private route: ActivatedRoute) {
    const idParam = this.route.snapshot.paramMap.get('id');
    if (idParam) {
      const id = Number(idParam);
      const existing = this.svc.getById(id);
      if (existing) {
        this.model = { ...existing };
        this.isEdit = true;
      }
    }
  }

  onSubmit(form: NgForm) {
    if (this.isEdit) {
      this.svc.update(this.model);
    } else {
      const { id, ...payload } = this.model;
      this.svc.add(payload);
    }
    this.router.navigate(['/subjects']);
  }

  onDelete() {
    if (this.isEdit && this.model.id) {
      this.svc.remove(this.model.id);
      this.router.navigate(['/subjects']);
    }
  }

  goBack() {
    this.router.navigate(['/subjects']);
  }
}
