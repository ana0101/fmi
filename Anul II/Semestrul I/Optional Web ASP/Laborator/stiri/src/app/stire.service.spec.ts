import { TestBed } from '@angular/core/testing';

import { StireService } from './stire.service';

describe('StireService', () => {
  let service: StireService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(StireService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
