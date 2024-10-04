// Load the WebFont script
const script = document.createElement('script');
script.src = 'https://ajax.googleapis.com/ajax/libs/webfont/1.6.26/webfont.js';
script.onload = () => {
    WebFont.load({
        google: {
            families: ['Press Start 2P']
        }
    });
};
document.head.appendChild(script);

