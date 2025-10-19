import { ComponentFixture, TestBed } from '@angular/core/testing';

import { Pag1Component } from './pag1.component';

describe('Pag1Component', () => {
  let component: Pag1Component;
  let fixture: ComponentFixture<Pag1Component>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [Pag1Component]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(Pag1Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
