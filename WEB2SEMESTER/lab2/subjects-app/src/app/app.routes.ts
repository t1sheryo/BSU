import { Routes } from '@angular/router';
import { SubjectCenter } from './subjects/subject-center/subject-center';
import { SubjectList } from './subjects/subject-list/subject-list';
import { SubjectInfo } from './subjects/subject-info/subject-info';
import { AddSubject } from './subjects/add-subject/add-subject';
import { SUBJECT_ROUTES } from './subjects/subject.routes';
import { ServiceCenter } from './services/service-center/service-center';
import { ServiceListComponent } from './services/service-list/service-list';
import { ServiceDetailsComponent } from './services/service-details/service-details';

export const routes: Routes = [
  { path: '', redirectTo: 'services', pathMatch: 'full' },
  {
    path: 'services',
    component: ServiceCenter,
    children: [
      { path: '', component: ServiceListComponent },
      { path: ':id', component: ServiceDetailsComponent }
    ]
  },
  {
    path: 'subjects',
    component: SubjectCenter,
    children: SUBJECT_ROUTES
  },
  { path: 'subjects/add', component: AddSubject },
  { path: '**', redirectTo: 'subjects' }
];
