import { ComponentFixture, TestBed } from '@angular/core/testing';
import { RouterTestingModule } from '@angular/router/testing';
import { of } from 'rxjs';
import { ServiceListComponent } from './service-list';
import { FirestoreService } from '../../services/firestore.service';

describe('ServiceListComponent', () => {
  let component: ServiceListComponent;
  let fixture: ComponentFixture<ServiceListComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [RouterTestingModule],
      declarations: [ServiceListComponent],
      providers: [
        {
          provide: FirestoreService,
          useValue: { getServices: () => of([]) }
        }
      ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ServiceListComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
