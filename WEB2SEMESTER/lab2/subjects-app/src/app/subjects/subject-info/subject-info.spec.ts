import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SubjectInfo } from './subject-info';

describe('SubjectInfo', () => {
  let component: SubjectInfo;
  let fixture: ComponentFixture<SubjectInfo>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SubjectInfo]
    })
    .compileComponents();

    fixture = TestBed.createComponent(SubjectInfo);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
