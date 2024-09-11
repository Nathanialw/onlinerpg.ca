'use strict'

const getElement = (selector) => {
  const el = document.querySelector(selector);
  if (el) return el;
  throw new Error(`Please check your classes : ${selector} does not exist`);
};

const navToggle = getElement(".bars");
const links = getElement(".nav-links");

navToggle.addEventListener("click", () => {
  links.classList.toggle("show-links");
});


