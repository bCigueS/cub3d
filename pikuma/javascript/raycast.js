// Map Grid

const	TILE_SIZE = 32;
const	MAP_NUM_ROWS = 11;
const	MAP_NUM_COLS = 15;
// Canvas
const	WINDOW_WIDTH = TILE_SIZE * MAP_NUM_COLS;
const	WINDOW_HEIGHT = TILE_SIZE * MAP_NUM_ROWS;

// Definition of the field of view in radian
const FOV_ANGLE = 60 * (Math.PI / 180);

// Width of each column in pixel
const WALL_STRIP_WIDTH = 32;
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;


class Player {
	constructor() {
		this.x = WINDOW_WIDTH / 2;
		this.y = WINDOW_HEIGHT / 2;
		this.radius = 5;
		this.turnDirection = 0; // -1 if fo left 1 if go right;
		this.walkDirection = 0; // -1 if go back 1 if go front
		this.rotationAngle = Math.PI / 2;
		this.moveSpeed = 3.0; // Pixel per frame of update mouvement
		this.rotationSpeed = 3 * (Math.PI / 180);
	}
	update() {
		this.rotationAngle += this.turnDirection * this.rotationSpeed;
		// Verifier que l'on est pas sur un mur 
		var	moveStep = this.walkDirection * this.moveSpeed;
		var	newX = this.x + (Math.cos(this.rotationAngle) * moveStep);
		var	newY = this.y + (Math.sin(this.rotationAngle) * moveStep);
		if (grid.is_aWall(newX, newY) == 0) {
			this.x = newX; 
			this.y = newY; 
		}
	}
	render() {
		noStroke();
		fill("#FF0000");
		circle(this.x, this.y, this.radius);
		stroke("red");
		//line(this.x,
		//	this.y,
		//this.x + (Math.cos(this.rotationAngle) * 50),
		//	this.y + (Math.sin(this.rotationAngle) * 50))
	}
}

class Map { // Definition of the map
	constructor() {
		this.grid = [
			[1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
		];
	}
	is_aWall(x, y) {
		// Out of bound
		if ((x > WINDOW_WIDTH || x < 0) || (y > WINDOW_HEIGHT || y < 0))
			return (1);
		var	mapGridX = Math.floor(x / TILE_SIZE);
		var mapGridY = Math.floor(y / TILE_SIZE);
		return grid.grid[mapGridY][mapGridX];
	}
	lineLength(x, y, rotation) {
		// Je vais envoyer this.x + (Math.cos(this.rotationAngle))
		var i = 0;
		var	newX = x + (Math.cos(rotation) * i);
		var	newY = y + (Math.cos(rotation) * i);
		for (i; this.is_aWall(newX, newY) == 0; i++) {
			newX = x + (Math.cos(rotation) * i);
			newY = y + (Math.cos(rotation) * i);
		}
		return i;
	}
	render() {
		for (var i = 0; i < MAP_NUM_ROWS; i++) {
			for (var j = 0; j < MAP_NUM_COLS; j++) {
				var tileX = TILE_SIZE * j;
				var tileY = TILE_SIZE * i;
				var	tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
				stroke("#222");
				fill(tileColor);
				rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
			}
		}
	}
}

class Ray {
	constructor(rayAngle) {
		this.rayAngle = rayAngle;
		this.wallHitX = 0;
		this.wallHitY = 0;
		this.distance = 0;

		// Il est important de trouver vers ou pointe le rayon pour faire les bon calcul au bon endroit 
		this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
		this.isRayFacingUp = !this.isRayFacingDown;
		// On oublie que l'on est en radian 
		this.isRayFacingRight = this.ranAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
		this.isRayFacingLeft = !this.isRayFacingRight;
		// Maintenant que je sais dans quel direction va le rayon, je vais pouvoir savoir si je dois rajouter un tile size pour mon yintercept
	}
	cast(columnId) {
		// xstep ystep --> deltaX deltaY
		// xintercept yintercept --> endroit ou j'intercept un mur la premier fois 
		var xintercept, yintercept;
		var xstep, ystep;

		yintercept = Math.floor(player.y/TILE_SIZE) * TILE_SIZE;
		if (this.isRayFacingDown)
			yintercept += TILE_SIZE;
		xintercept = player.x + ((yintercept - player.y) / Math.tan(this.rayAngle));
		ystep = TILE_SIZE;
		if (this.isRayFacingUp)
			ystep *= -1;
		xstep = TILE_SIZE / Math.tan(this.rayAngle);
		if (this.isRayFacingLeft && xstep > 0)
			xstep *= -1;
		if (this.isRayFacingRight && xstep < 0)
			xstep *= -1;

		var nextHorzTouchX = xintercept;
		var nextHorzTouchY = yintercept;
	}
	render() {
		line(player.x, player.y, player.x + Math.cos(this.rayAngle) * 30 , player.y + Math.sin(this.rayAngle) * 30);
	}
}

var	grid = new Map();
var	player = new Player();
var	rays = [];

function keyPressed() {
	if (keyCode == UP_ARROW) {
		player.walkDirection = 1;
	}
	else if (keyCode == DOWN_ARROW) {
		player.walkDirection = -1;
	}
	else if (keyCode == RIGHT_ARROW) {
		player.turnDirection = 1;
	}
	else if (keyCode == LEFT_ARROW) {
		player.turnDirection = -1;
	}
}

function keyReleased() {
	if (keyCode == UP_ARROW) {
		player.walkDirection = 0;
	}
	else if (keyCode == DOWN_ARROW) {
		player.walkDirection = 0;
	}
	else if (keyCode == RIGHT_ARROW) {
		player.turnDirection = 0;
	}
	else if (keyCode == LEFT_ARROW) {
		player.turnDirection = 0;
	}
}

// Init all object (p5.js)
function setup() {
	createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}


// Permet de securiser cette valeur et d'eviter les valeurs negatives ou des valeurs au dela de 2pi (360 deg)
function normalizeAngle(angle) {
	angle = angle / (2  * Math.PI);
	if (angle < 0) {
		angle += (2 * Math.PI);
	}
	return angle;
}

function castAllRays() {
	var columnId = 0;

	var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

	rays = [];
	//for (var i = 0; i < NUM_RAYS; i++) {
	for ( var i = 0; i < 1; i++) {
		var ray = new Ray(rayAngle);
		ray.cast(columnId);
		rays.push(ray);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		columnId++;
	}
}

//Update all fame object before we render the next frame
function update() {
	player.update();
	castAllRays();
}

// Render all object frame by frame (p5.js)
function draw() {
	grid.render();
	player.render();
	for (ray of rays) {
		ray.render();
	}
	update();
}

	// The idea to find the wall collision is to find the horizontal collision than the vertical collision, than compare the distance between the player and the wall.
	// deltaX value = distance entre deux colision horizontal  
	// deltaY value = distance entre deux colision vertical 
	// Un fois qu'on a trouver deux intersection, il suffit de rajouter le delta pour arriver a la colision suivante.
	// Dans Wold3d ils ont appele ca xstep et ystep

	/*
	*	soh -> sin = Opposit/Hypo
	*	cah -> cos = Adjacent/Hypo
	*	toa -> tan = Opposit/Adjacent
	*
	*	 L'idee est d'utiliser la position du jouer pour trouver le y le plus proche.
	*	 On va donc diviser la position en y du joueur par la taille en pixel de chaque tile, et arrondir la valeur. On va ensuite la mutipliser par la taille en pixel d'une tuile pour recuperer le y le plus proche pour la colision.
	*
	*	Ay = Math.floor(player.y/32) * 32;
*	 	Je peux utiliser tan pour trouver la valeur de x maintenant que j'ai le y.
	*	Je calcul la distance entre py et pa pour obtenir le cote opose
	*	p.y = 150
	*	a.y = 128
	*	Oppose = py - ay = 22;
*		Adjacent = px + (py - ay) / tan(angle) 
	*
	*/
