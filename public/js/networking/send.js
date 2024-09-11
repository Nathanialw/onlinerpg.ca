'use strict'


const request = new XMLHttpRequest()
const method = "GET"
const url = "www.onlinerpg.ca"
request.open(method, url, true)
//request.send()
//request.log(request)

export function sendMessage(direction) {
    request.send("0" + direction)
}
