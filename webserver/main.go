package main

import (
	"fmt"
	"github.com/julienschmidt/httprouter"
	"html/template"
	"net/http"
)

type PageData struct {
	Title string
	Body  string
}

func main() {
	r := httprouter.New()
	r.GET("/goapp", homeHandler)
	server := http.Server{
		Addr:    "localhost:9001",
		Handler: r,
	}

	err := server.ListenAndServe()
	if err != nil {
		fmt.Println(err)
	}
}

func homeHandler(w http.ResponseWriter, r *http.Request, p httprouter.Params) {
	fmt.Printf("message received from %s\n"+p.ByName("name"), r.RemoteAddr)

	data := PageData{
		Title: "My Page Title",
		Body:  "Welcome to my dwebsite!",
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
}

func productHandler(w http.ResponseWriter, r *http.Request) {
	// Handle requests for individual products here
}

func usersHandler(w http.ResponseWriter, r *http.Request) {
	// Handle requests for the user API here
}
``