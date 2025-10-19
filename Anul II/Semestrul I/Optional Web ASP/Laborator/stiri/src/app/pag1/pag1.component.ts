import { Component, OnDestroy, OnInit } from '@angular/core';
import { RouterModule } from '@angular/router';
import { StireComponent } from '../stire/stire.component';
import { Stire } from '../stire';
import { CommonModule } from '@angular/common';
import { Observable, Subscription, interval, take } from 'rxjs';
import { StireService } from '../stire.service';
import { User } from '../user';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-pag1',
  standalone: true,
  imports: [RouterModule, CommonModule, StireComponent],
  templateUrl: './pag1.component.html',
  styleUrl: './pag1.component.scss'
})
export class Pag1Component implements OnInit {
  readonly APIUrl="https://localhost:7043/api/Stiri/";

  constructor(private http:HttpClient) {}

  /*ngOnDestroy(): void {
    this.sourceSubscription.unsubscribe();
  }*/

  /*ngOnInit(): void {
    this.source$ = interval(2000);
    this.sourceSubscription = this.source$.subscribe((x) => console.log(x));
    this.stireService.getUsers().pipe(take(1)).subscribe(
      (x: User[]) => {
      console.log(x);
      x.forEach((user: User) => {
        console.log(user.first_name);
      });
    });
  }*/

  /// public source$!: Observable<number>;
  // public sourceSubscription!: Subscription;

  superStire: any=[];

  refreshStiri() {
    this.http.get(this.APIUrl).subscribe(data => {
      this.superStire = data;
    })
  }

  ngOnInit(): void {
    /*this.source$ = interval(2000);
    this.sourceSubscription = this.source$.subscribe((x) => console.log(x));
    this.stireService.getUsers().pipe(take(1)).subscribe(
      (x: User[]) => {
      console.log(x);
      x.forEach((user: User) => {
        console.log(user.first_name);
      });
    });*/
    this.refreshStiri();
  }
}
