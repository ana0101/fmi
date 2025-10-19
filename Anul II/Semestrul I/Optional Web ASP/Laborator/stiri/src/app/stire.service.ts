import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs/internal/Observable';
import { User } from './user';
import { map } from 'rxjs';
import { GetUsersResponse } from './get-users-response';
import { Stire } from './stire';

@Injectable({
  providedIn: 'root'
})
export class StireService {

  constructor(private http: HttpClient) { }
  public getUrl: string = "https://reqres.in/api/users";
  public hello():void {
    alert("Hello!");
  }

  public getUsers(): Observable<User[]> {
    return this.http.get<GetUsersResponse>(this.getUrl)
    .pipe(map((resp) => resp.data));
  }

  public addStire(stire: Stire): Observable<User[]> {
    return this.http.get<GetUsersResponse>(this.getUrl)
    .pipe(map((resp) => resp.data));
    //return this.http.post<any>(this.postUrl, stire);
  }
}
