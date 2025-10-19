import { Component, Input, OnChanges, OnDestroy, OnInit, SimpleChanges } from '@angular/core';
import { Stire } from '../stire';

@Component({
  selector: 'app-stire',
  standalone: true,
  imports: [],
  templateUrl: './stire.component.html',
  styleUrl: './stire.component.scss'
})
export class StireComponent implements OnInit, OnChanges, OnDestroy{
  @Input() public stire: Stire = {
    titlu: "Titlu1",
    autor: "Autor1",
    lead: "Lead1",
    data: "Data1"
  };
  ngOnInit(): void {
    console.log('S-a apelat OnInit din componenta Stire');
  }
  ngOnChanges(changes: SimpleChanges): void {
    console.log('S-a apelat OnChanges din componenta Stire');
  }
  ngOnDestroy(): void {
    console.log('S-a apelat OnDestroy din componenta Stire');
  }

}
