import { Injectable } from '@angular/core';
import { Subject } from '../subject';
import { MOCK_SUBJECTS } from '../mock-subject-list';

@Injectable({
  providedIn: 'root'
})
export class SubjectService {
  private subjects: Subject[] = [...MOCK_SUBJECTS];

  getAll(): Subject[] {
    return [...this.subjects];
  }

  getById(id: number): Subject | undefined {
    return this.subjects.find(s => s.id === id);
  }

  add(subject: Omit<Subject, 'id'>): Subject {
    const newId = this.subjects.length ? Math.max(...this.subjects.map(s => s.id)) + 1 : 1;
    const created: Subject = { id: newId, ...subject };
    this.subjects = [...this.subjects, created];
    return created;
  }

  update(updated: Subject): boolean {
    const index = this.subjects.findIndex(s => s.id === updated.id);
    if (index === -1) return false;
    const copy = [...this.subjects];
    copy[index] = { ...updated };
    this.subjects = copy;
    return true;
  }

  remove(id: number): boolean {
    const exists = this.subjects.some(s => s.id === id);
    if (!exists) return false;
    this.subjects = this.subjects.filter(s => s.id !== id);
    return true;
  }
}
