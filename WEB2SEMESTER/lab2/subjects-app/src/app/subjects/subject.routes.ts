import { Routes } from '@angular/router';
import { SubjectList } from './subject-list/subject-list';
import { SubjectInfo } from './subject-info/subject-info';
import { AddSubject } from './add-subject/add-subject';

export const SUBJECT_ROUTES: Routes = [
  { path: '', component: SubjectList },
  { path: 'add', component: AddSubject },
  { path: 'edit/:id', component: AddSubject },
  { path: ':id', component: SubjectInfo }
];


