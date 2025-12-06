import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SubjectCenter } from './subject-center';

describe('SubjectCenter', () => {
  let component: SubjectCenter;
  let fixture: ComponentFixture<SubjectCenter>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SubjectCenter]
    })
    .compileComponents();

    fixture = TestBed.createComponent(SubjectCenter);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
