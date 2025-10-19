import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormsModule, ReactiveFormsModule, Validators } from '@angular/forms';
import { StireService } from '../stire.service';
import { take } from 'rxjs';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-pag2',
  standalone: true,
  imports: [FormsModule, ReactiveFormsModule],
  templateUrl: './pag2.component.html',
  styleUrl: './pag2.component.scss'
})
export class Pag2Component implements OnInit {
  readonly APIUrl="https://localhost:7043/api/Stiri/";

  constructor(private http:HttpClient) {}
  //constructor(private service: StireService) {}

  ngOnInit(): void {
    this.myForm = new FormGroup({
      titlu: new FormControl('', Validators.required),
      lead: new FormControl(''),
      continut: new FormControl(''),
      autor: new FormControl(''),
      categorieId: new FormControl('')
    });
  }
  public myForm!: FormGroup;

  public adaugaStire(form: FormGroup): void {
    if (form.invalid) {
      console.log("invalid");
    }
    else {
      this.http.post<FormGroup>(this.APIUrl, form.value).pipe(take(1)).subscribe();
    }
    console.log(1, form);
  }
}