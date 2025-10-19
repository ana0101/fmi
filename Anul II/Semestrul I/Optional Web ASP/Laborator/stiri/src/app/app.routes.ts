import { Routes } from '@angular/router';
import { Pag1Component } from './pag1/pag1.component';
import { Pag2Component } from './pag2/pag2.component';

export const routes: Routes = [
    {
        path: "",
        component: Pag1Component
    },
    {
        path: "pag2",
        component: Pag2Component
    }
];
