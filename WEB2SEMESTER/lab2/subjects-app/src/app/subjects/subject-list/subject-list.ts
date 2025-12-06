import { Component } from '@angular/core';
import { RouterLink } from '@angular/router';
import { SubjectService } from '../services/subject.service';
import { Subject } from '../subject';

@Component({
  selector: 'app-subject-list',
  imports: [RouterLink],
  template: `
    <div class="card">
      <div class="card-body">
        <div class="d-flex justify-content-between align-items-center mb-3">
          <h5 class="card-title mb-0">Список предметов</h5>
          <a class="btn btn-sm btn-primary" [routerLink]="['/subjects','add']">Добавить</a>
        </div>
        <table class="table table-sm">
          <thead>
            <tr>
              <th>#</th>
              <th>Название</th>
              <th>Преподаватель</th>
              <th>Кредиты</th>
              <th></th>
            </tr>
          </thead>
          <tbody>
            @for (s of subjects; track s.id) {
              <tr>
                <td>{{ s.id }}</td>
                <td><a [routerLink]="['/subjects', s.id]">{{ s.name }}</a></td>
                <td>{{ s.teacher }}</td>
                <td>{{ s.credits }}</td>
                <td>
                  <a class="btn btn-sm btn-outline-secondary" [routerLink]="['/subjects','edit', s.id]">Править</a>
                </td>
              </tr>
            }
          </tbody>
        </table>
      </div>
    </div>
  `,
  styles: ``
})
export class SubjectList {
  subjects: Subject[] = [];

  constructor(private svc: SubjectService) {
    this.subjects = this.svc.getAll();
  }
}
