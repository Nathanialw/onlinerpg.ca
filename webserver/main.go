package main

import (
	"html/template"
	"net/http"
)

type PageData struct {
	Title string
	Body  string
}

func main() {
	http.HandleFunc("/goapp/", func(w http.ResponseWriter, r *http.Request) {
		data := PageData{
			Title: "My Page Title",
			Body:  "Welcome to my website!",
		}

		tmpl, err := template.ParseFiles("template.html")
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}

		err = tmpl.Execute(w, data)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
		}
	})

	http.ListenAndServe(":8080", nil)
}
