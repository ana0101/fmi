import { Component } from '@angular/core';

@Component({
  selector: 'app-banner',
  standalone: true,
  imports: [],
  templateUrl: './banner.component.html',
  styleUrl: './banner.component.scss'
})
export class BannerComponent {
  public url: string = "https://media.istockphoto.com/id/1183338499/ro/vector/0547.webp?s=1024x1024&w=is&k=20&c=hciemnykrctRSa8xoeCVxy7PsDTFF-NrT3zVwPcRiZw=";
}
