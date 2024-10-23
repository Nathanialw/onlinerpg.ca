

// add html to newGame.html

{/* <section class="options-container">
    <article class='options'>    
        <ul>
            <li class="option"><button id="Human" class='btn btn-block'>Human</button></li>
            <li class="option"><button id="Elf" class='btn btn-block'>Elf</button></li>
            <!-- <li><button id="Orc" class='btn btn-submit'>Orc</button></li> -->
            <!-- <li><button id="Dwarf" class='btn btn-submit'>Dwarf</button></li> -->
            <!-- <li><button id="Goblin" class='btn btn-submit'>Goblin</button></li> -->
        </ul>

        <ul>
            <li class="option"><button id="Male" class='btn btn-block'>Male</button></li>
            <li class="option"><button id="Female" class='btn btn-block'>Female</button></li>
        </ul>

        <ul>
            <li class="option"><button id="Fighter" class='btn btn-block'>Fighter</button></li>
            <li class="option"><button id="Mystic" class='btn btn-block'>Mystic</button></li>
        </ul>

        <ul>
            <li class="option"><button id="Good" class='btn btn-block'>Good</button></li>
            <li class="option"><button id="Neutral" class='btn btn-block'>Neutral</button></li>
            <li class="option"><button id="Evil" class='btn btn-block'>Evil</button></li>
        </ul>
    </section>
</section>

<section class="hero-wrapper">
    <h1 id="hero-class" class="hero-class"></h1>
</section>

<section class='nameInput'>
    <form method='POST' id="myForm">
        <input class="form-input form-row" type="text" id="name" name="name" value="" required minlength="3" maxlength="20" autocomplete="off">
        <br> 
    </form>
</section>

<section class='startButton button'>
    <button id="startGame" class='btn btn-center'>Start Game</button>
    <br> 
    <div id="nameError" class="error-message" style="color: red; display: none;">Name must be at least 3 characters long.</div>
    <div id="loading-text" class="loading-message" style="color: white; display: none;">Loading...</div>
</section> */}

export function character_Create() {
    const content = document.getElementById('chracterCreate');

    // Create options container
    const optionsContainer = document.createElement('section');
    optionsContainer.classList.add('options-container');

    const optionsArticle = document.createElement('article');
    optionsArticle.classList.add('options');
    optionsContainer.appendChild(optionsArticle);

    // Create options lists
    const races = ['Human', 'Elf'];
    const genders = ['Male', 'Female'];
    const classes = ['Fighter', 'Mystic'];
    const alignments = ['Good', 'Neutral', 'Evil'];

    const createOptionList = (options) => {
        const ul = document.createElement('ul');
        options.forEach(option => {
            const li = document.createElement('li');
            li.classList.add('option');
            const button = document.createElement('button');
            button.id = option;
            button.classList.add('btn', 'btn-block');
            button.textContent = option;
            li.appendChild(button);
            ul.appendChild(li);
        });
        return ul;
    };

    optionsArticle.appendChild(createOptionList(races));
    optionsArticle.appendChild(createOptionList(genders));
    optionsArticle.appendChild(createOptionList(classes));
    optionsArticle.appendChild(createOptionList(alignments));

    content.appendChild(optionsContainer);

    // Create hero wrapper
    const heroWrapper = document.createElement('section');
    heroWrapper.classList.add('hero-wrapper');
    const heroClass = document.createElement('h1');
    heroClass.id = 'hero-class';
    heroClass.classList.add('hero-class');
    heroWrapper.appendChild(heroClass);
    content.appendChild(heroWrapper);

    // Create name input section
    const nameInputSection = document.createElement('section');
    nameInputSection.classList.add('nameInput');
    const form = document.createElement('form');
    form.method = 'POST';
    form.id = 'myForm';
    const input = document.createElement('input');
    input.classList.add('form-input', 'form-row');
    input.type = 'text';
    input.id = 'name';
    input.name = 'name';
    input.required = true;
    input.minLength = 3;
    input.maxLength = 20;
    input.autocomplete = 'off';
    form.appendChild(input);
    nameInputSection.appendChild(form);
    content.appendChild(nameInputSection);

    // Create start button section
    const startButtonSection = document.createElement('section');
    startButtonSection.classList.add('startButton', 'button');
    const startButton = document.createElement('button');
    startButton.id = 'startGame';
    startButton.classList.add('btn', 'btn-center');
    startButton.textContent = 'Start Game';
    startButtonSection.appendChild(startButton);

    const nameError = document.createElement('div');
    nameError.id = 'nameError';
    nameError.classList.add('error-message');
    nameError.textContent = 'Name must be at least 3 characters long.';
    startButtonSection.appendChild(nameError);

    const loadingText = document.createElement('div');
    loadingText.id = 'loading-text';
    loadingText.classList.add('loading-message');
    loadingText.textContent = 'Loading...';
    startButtonSection.appendChild(loadingText);

    content.appendChild(startButtonSection);
});