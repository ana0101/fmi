import { User } from "./user";

export interface GetUsersResponse {
    data: User[];
    page: number;
    per_page: number;
    suport: Object;
    total: number;
    total_pages: number;
}
