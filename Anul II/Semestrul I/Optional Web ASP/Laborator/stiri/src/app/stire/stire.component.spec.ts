import { ComponentFixture, TestBed } from '@angular/core/testing';

import { StireComponent } from './stire.component';

describe('StireComponent', () => {
  let component: StireComponent;
  let fixture: ComponentFixture<StireComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [StireComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(StireComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
