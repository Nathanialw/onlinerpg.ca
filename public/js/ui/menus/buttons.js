'use strict'






////menu buttons
// Load textures
    // await Assets.load([
    //     'https://pixijs.com/assets/bg_button.jpg',
    //     'https://pixijs.com/assets/button.png',
    //     'https://pixijs.com/assets/button_down.png',
    //     'https://pixijs.com/assets/button_over.png',
    // ]);


    // Create some textures from an image path
    // const textureButton = Texture.from('https://pixijs.com/assets/button.png');
    // const textureButtonDown = Texture.from('https://pixijs.com/assets/button_down.png');
    // const textureButtonOver = Texture.from('https://pixijs.com/assets/button_over.png');

    // const buttons = [];

    // const buttonPositions = [175, 75, 655, 75, 410, 325, 150, 465, 685, 445];

    // for (let i = 0; i < 5; i++)
    // {
    //     const button = new Sprite(textureButton);

    //     button.cursor = 'hover';

    //     button.anchor.set(0.5);
    //     button.x = buttonPositions[i * 2];
    //     button.y = buttonPositions[i * 2 + 1];

    //     // Make the button interactive...
    //     button.eventMode = 'static';

    //     button
    //         .on('pointerdown', onButtonDown)
    //         .on('pointerup', onButtonUp)
    //         .on('pointerupoutside', onButtonUp)
    //         .on('pointerover', onButtonOver)
    //         .on('pointerout', onButtonOut);

    //     // Add it to the stage
    //     app.stage.addChild(button);

    //     // Add button to array
    //     buttons.push(button);
    // }

    // function onButtonDown()
    // {
    //     this.isdown = true;
    //     this.texture = textureButtonDown;
    //     this.alpha = 1;
    // }

    // function onButtonUp()
    // {
    //     this.isdown = false;
    //     if (this.isOver)
    //     {
    //         this.texture = textureButtonOver;
    //     }
    //     else
    //     {
    //         this.texture = textureButton;
    //     }
    // }

    // function onButtonOver()
    // {
    //     this.isOver = true;
    //     if (this.isdown)
    //     {
    //         return;
    //     }
    //     this.texture = textureButtonOver;
    // }

    // function onButtonOut()
    // {
    //     this.isOver = false;
    //     if (this.isdown)
    //     {
    //         return;
    //     }
    //     this.texture = textureButton;
    // }

/////////////////////////////////