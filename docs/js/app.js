// ============================================
// TinyFilmFestival Documentation App
// ============================================

document.addEventListener('DOMContentLoaded', () => {
    const sidebar = document.getElementById('sidebar');
    const overlay = document.getElementById('overlay');
    const menuToggle = document.querySelector('.menu-toggle');
    const content = document.getElementById('content');
    const navLinks = document.querySelectorAll('.nav-section a[data-page]');
    const searchInput = document.getElementById('search-input');
    const searchResults = document.getElementById('search-results');

    // Search functionality
    searchInput.addEventListener('input', (e) => {
        const query = e.target.value.toLowerCase().trim();
        
        if (query.length < 2) {
            searchResults.innerHTML = '';
            searchResults.classList.remove('visible');
            return;
        }
        
        const results = searchAPI(query);
        displaySearchResults(results, query);
    });

    searchInput.addEventListener('focus', () => {
        if (searchInput.value.length >= 2) {
            searchResults.classList.add('visible');
        }
    });

    document.addEventListener('click', (e) => {
        if (!e.target.closest('.search-container')) {
            searchResults.classList.remove('visible');
        }
    });

    // Mobile menu toggle
    menuToggle.addEventListener('click', () => {
        sidebar.classList.toggle('open');
        overlay.classList.toggle('visible');
    });

    overlay.addEventListener('click', () => {
        sidebar.classList.remove('open');
        overlay.classList.remove('visible');
    });

    // Navigation - regular links
    navLinks.forEach(link => {
        link.addEventListener('click', (e) => {
            e.preventDefault();
            const page = link.dataset.page;
            
            // Check if this is an expandable toggle
            if (link.classList.contains('nav-expand-toggle')) {
                const parent = link.closest('.nav-expandable');
                parent.classList.toggle('expanded');
                // Don't navigate, just expand
                return;
            }
            
            // Update active state
            navLinks.forEach(l => l.classList.remove('active'));
            link.classList.add('active');
            
            // Load page content
            loadPage(page);
            
            // Close mobile menu
            sidebar.classList.remove('open');
            overlay.classList.remove('visible');
            
            // Scroll to top
            window.scrollTo(0, 0);
        });
    });

    // Load initial page
    const hash = window.location.hash.slice(1) || 'home';
    loadPage(hash);

    // Handle back/forward navigation
    window.addEventListener('popstate', () => {
        const hash = window.location.hash.slice(1) || 'home';
        loadPage(hash, false);
    });
});

function loadPage(page, updateHistory = true) {
    const content = document.getElementById('content');
    const pageContent = pages[page] || pages['home'];
    
    content.innerHTML = pageContent;
    
    // Update URL
    if (updateHistory) {
        history.pushState(null, '', `#${page}`);
    }
    
    // Update active nav link
    document.querySelectorAll('.nav-section a[data-page]').forEach(link => {
        link.classList.toggle('active', link.dataset.page === page);
    });
    
    // Re-run Prism for syntax highlighting
    if (typeof Prism !== 'undefined') {
        Prism.highlightAll();
    }
}

// Search index - methods and their locations
const searchIndex = [
    // Simple LED Mode
    { method: 'ledBegin()', description: 'Initialize the LED matrix', page: 'simple-led', category: 'Simple LED' },
    { method: 'ledWrite(x, y, state)', description: 'Set LED at coordinates to HIGH or LOW', page: 'simple-led', category: 'Simple LED' },
    { method: 'ledWrite(index, state)', description: 'Set LED by linear index (0-95)', page: 'simple-led', category: 'Simple LED' },
    { method: 'ledRead(x, y)', description: 'Read current state of an LED', page: 'simple-led', category: 'Simple LED' },
    { method: 'ledToggle(x, y)', description: 'Toggle LED between ON and OFF', page: 'simple-led', category: 'Simple LED' },
    { method: 'ledClear()', description: 'Turn off all LEDs', page: 'simple-led', category: 'Simple LED' },
    
    // Animation Mode
    { method: 'begin()', description: 'Initialize the LED matrix for TinyScreen', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'play(animation, mode)', description: 'Start playing an animation', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'play(animation, mode, start, end)', description: 'Play animation with frame range', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'pause()', description: 'Pause current animation', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'resume()', description: 'Resume paused animation', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'stop()', description: 'Stop animation and clear display', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'update()', description: 'Update animation frame (call every loop)', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'setSpeed(multiplier)', description: 'Change playback speed', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'restoreOriginalSpeed()', description: 'Reset to original timing', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'getCurrentSpeed()', description: 'Get current speed multiplier', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'isPlaying()', description: 'Check if animation is playing', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'isPaused()', description: 'Check if animation is paused', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'isComplete()', description: 'Check if ONCE mode finished', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'getCurrentFrame()', description: 'Get current frame number', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'getTotalFrames()', description: 'Get total number of frames', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'addLayer()', description: 'Add a new animation layer', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'playOnLayer(layer, anim, mode)', description: 'Play animation on specific layer', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'setSpeedOnLayer(layer, speed)', description: 'Set speed for specific layer', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'pauseLayer(layer)', description: 'Pause specific layer', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'resumeLayer(layer)', description: 'Resume specific layer', page: 'animation-mode', category: 'Animation Mode' },
    { method: 'stopLayer(layer)', description: 'Stop specific layer', page: 'animation-mode', category: 'Animation Mode' },
    
    // Canvas Mode
    { method: 'beginDraw()', description: 'Begin a drawing operation', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'endDraw()', description: 'End drawing and display result', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'clear()', description: 'Clear the display', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'background(state)', description: 'Set background state (ON/OFF)', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'stroke(state)', description: 'Set outline state for shapes', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'noStroke()', description: 'Disable outlines', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'fill(state)', description: 'Set fill state for shapes', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'noFill()', description: 'Disable fill', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'point(x, y)', description: 'Draw a single point', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'line(x1, y1, x2, y2)', description: 'Draw a line between two points', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'rect(x, y, width, height)', description: 'Draw a rectangle', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'circle(cx, cy, radius)', description: 'Draw a circle', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'ellipse(cx, cy, width, height)', description: 'Draw an ellipse', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'text(string, x, y)', description: 'Draw text at position', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'textScrollSpeed(speed)', description: 'Set scroll speed for text', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'beginText(x, y)', description: 'Begin text block', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'endText()', description: 'End text block', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'print()', description: 'Print text', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'println()', description: 'Print text with newline', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'width()', description: 'Get matrix width (12)', page: 'canvas-mode', category: 'Canvas Mode' },
    { method: 'height()', description: 'Get matrix height (8)', page: 'canvas-mode', category: 'Canvas Mode' },
    
    // Hybrid Mode
    { method: 'beginOverlay()', description: 'Begin overlay drawing (preserves animation)', page: 'hybrid-mode', category: 'Hybrid Mode' },
    { method: 'endOverlay()', description: 'End overlay and display combined result', page: 'hybrid-mode', category: 'Hybrid Mode' },
    
    // Constants
    { method: 'LOOP', description: 'Play animation continuously', page: 'animation-mode', category: 'Constants' },
    { method: 'ONCE', description: 'Play animation once and stop', page: 'animation-mode', category: 'Constants' },
    { method: 'BOOMERANG', description: 'Play animation forward then backward', page: 'animation-mode', category: 'Constants' },
    { method: 'ON', description: 'LED/pixel on state', page: 'canvas-mode', category: 'Constants' },
    { method: 'OFF', description: 'LED/pixel off state', page: 'canvas-mode', category: 'Constants' },
    { method: 'HIGH', description: 'LED on (Simple LED mode)', page: 'simple-led', category: 'Constants' },
    { method: 'LOW', description: 'LED off (Simple LED mode)', page: 'simple-led', category: 'Constants' },
];

function searchAPI(query) {
    return searchIndex.filter(item => 
        item.method.toLowerCase().includes(query) ||
        item.description.toLowerCase().includes(query) ||
        item.category.toLowerCase().includes(query)
    ).slice(0, 10); // Limit to 10 results
}

function displaySearchResults(results, query) {
    const searchResults = document.getElementById('search-results');
    
    if (results.length === 0) {
        searchResults.innerHTML = '<div class="search-no-results">No results found</div>';
        searchResults.classList.add('visible');
        return;
    }
    
    const html = results.map(item => {
        const highlightedMethod = item.method.replace(
            new RegExp(`(${query})`, 'gi'),
            '<mark>$1</mark>'
        );
        return `
            <a href="#" class="search-result" data-page="${item.page}">
                <span class="search-method">${highlightedMethod}</span>
                <span class="search-category">${item.category}</span>
                <span class="search-desc">${item.description}</span>
            </a>
        `;
    }).join('');
    
    searchResults.innerHTML = html;
    searchResults.classList.add('visible');
    
    // Add click handlers to results
    searchResults.querySelectorAll('.search-result').forEach(result => {
        result.addEventListener('click', (e) => {
            e.preventDefault();
            const page = result.dataset.page;
            loadPage(page);
            searchResults.classList.remove('visible');
            document.getElementById('search-input').value = '';
            
            // Close mobile menu
            document.getElementById('sidebar').classList.remove('open');
            document.getElementById('overlay').classList.remove('visible');
        });
    });
}

// Page content
const pages = {
    'home': `
        <h1>TinyFilmFestival</h1>
        <p>A library for the Arduino UNO R4 WiFi's built-in 12×8 LED Matrix. One class, four modes.</p>

        <h2>Four Modes</h2>
        <div class="mode-grid">
            <div class="mode-card">
                <h4>Simple LED</h4>
                <p>Control individual LEDs like digitalWrite()</p>
                <code>ledWrite(), ledToggle(), ledClear()</code>
            </div>
            <div class="mode-card">
                <h4>Animation Mode</h4>
                <p>Play pre-made frame animations</p>
                <code>play(), pause(), setSpeed()</code>
            </div>
            <div class="mode-card">
                <h4>Canvas Mode</h4>
                <p>Draw with code in real-time</p>
                <code>beginDraw(), point(), line()</code>
            </div>
            <div class="mode-card">
                <h4>Hybrid Mode</h4>
                <p>Draw over animations</p>
                <code>beginOverlay(), endOverlay()</code>
            </div>
        </div>

        <h2>LED Matrix Layout</h2>
        <p>The R4 WiFi has a 12×8 LED matrix (96 LEDs total). Use (x, y) coordinates or linear index:</p>
        <div class="matrix-grid">     x=0  x=1  x=2  x=3  x=4  x=5  x=6  x=7  x=8  x=9  x=10 x=11
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=0 |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=1 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=2 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=3 | 36 | 37 | 38 | 39 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=4 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 58 | 59 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=5 | 60 | 61 | 62 | 63 | 64 | 65 | 66 | 67 | 68 | 69 | 70 | 71 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=6 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 | 81 | 82 | 83 |
    +----+----+----+----+----+----+----+----+----+----+----+----+
y=7 | 84 | 85 | 86 | 87 | 88 | 89 | 90 | 91 | 92 | 93 | 94 | 95 |
    +----+----+----+----+----+----+----+----+----+----+----+----+</div>
        <p>Numbers inside = linear index for <code>ledWrite(index, state)</code></p>

        <h2>Getting Started</h2>
        <p>Install the library, include it in your sketch, and start using one of the four modes:</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
    // Start using Animation, Canvas, or Hybrid mode
}

void loop() {
    screen.update();
}</code></pre>
    `,

    'installation': `
        <h1>Installation</h1>
        
        <h2>Arduino IDE Library Manager</h2>
        <ol>
            <li>Open Arduino IDE</li>
            <li>Go to <strong>Sketch → Include Library → Manage Libraries...</strong></li>
            <li>Search for "TinyFilmFestival"</li>
            <li>Click <strong>Install</strong></li>
        </ol>

        <h2>Manual Installation</h2>
        <ol>
            <li>Download the library from <a href="https://github.com/DigitalFuturesOCADU/TinyFilmFestival" target="_blank">GitHub</a></li>
            <li>Extract the ZIP file</li>
            <li>Copy the folder to your Arduino libraries directory:
                <ul>
                    <li><strong>macOS:</strong> ~/Documents/Arduino/libraries/</li>
                    <li><strong>Windows:</strong> Documents\\Arduino\\libraries\\</li>
                    <li><strong>Linux:</strong> ~/Arduino/libraries/</li>
                </ul>
            </li>
            <li>Restart Arduino IDE</li>
        </ol>

        <h2>Requirements</h2>
        <table>
            <tr>
                <th>Requirement</th>
                <th>Details</th>
            </tr>
            <tr>
                <td>Hardware</td>
                <td>Arduino UNO R4 WiFi</td>
            </tr>
            <tr>
                <td>Arduino IDE</td>
                <td>Version 2.0 or later</td>
            </tr>
            <tr>
                <td>Board Package</td>
                <td>Arduino UNO R4 Boards</td>
            </tr>
        </table>

        <div class="info-box note">
            <strong>Note</strong>
            The TinyFilmFestival library automatically includes ArduinoGraphics and Arduino_LED_Matrix, so you don't need to install or include them separately.
        </div>
    `,

    'quick-start': `
        <h1>Quick Start</h1>

        <h2>Simple LED Mode</h2>
        <p>Control individual LEDs like <code>digitalWrite()</code> — the simplest way to get started.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

void setup() {
    ledBegin();                   // Initialize matrix
    
    ledWrite(0, 0, HIGH);         // Top-left ON
    ledWrite(11, 7, HIGH);        // Bottom-right ON
    ledToggle(0, 0);              // Toggle top-left OFF
}

void loop() {
    ledWrite(5, 3, HIGH);         // Center ON
    delay(500);
    ledWrite(5, 3, LOW);          // Center OFF
    delay(500);
}</code></pre>

        <h2>Animation Mode</h2>
        <p>Play pre-made frame animations created in the LED Matrix Editor.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"               // Your animation file

TinyScreen screen;
Animation myAnim = idle;        // Variable name from .h file

void setup() {
    screen.begin();
    screen.play(myAnim, LOOP);
}

void loop() {
    screen.update();
}</code></pre>

        <h2>Canvas Mode</h2>
        <p>Draw graphics with code using Processing-style commands.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    screen.point(5, 3);           // Draw a point
    screen.line(0, 0, 11, 7);     // Draw a line
    screen.endDraw();
}</code></pre>

        <h2>Hybrid Mode</h2>
        <p>Draw over animations — the best of both worlds.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "myAnimation.h"

TinyScreen screen;
Animation anim = animation;

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    screen.update();
    
    screen.beginOverlay();
    screen.point(11, 0);          // Status indicator
    screen.endOverlay();
}</code></pre>
    `,

    'editor-guide': `
        <h1>LED Matrix Editor</h1>
        <p>The <a href="https://ledmatrix-editor.arduino.cc/" target="_blank">Arduino LED Matrix Editor</a> provides a visual interface for creating LED matrix animations.</p>

        <h2>Features</h2>
        <ul>
            <li>Create animations by painting/erasing pixels frame by frame</li>
            <li>Copy frames for easy transitions</li>
            <li>Move pixels as a group within a frame</li>
            <li>Set display time for each frame</li>
        </ul>

        <h2>Keyboard Shortcuts</h2>
        
        <h3>Project Controls</h3>
        <table>
            <tr><th>Action</th><th>Shortcut</th></tr>
            <tr><td>Start/Stop preview</td><td>Spacebar</td></tr>
            <tr><td>Preview with loop</td><td>⇧ + Spacebar</td></tr>
            <tr><td>Upload project</td><td>Ctrl + U</td></tr>
            <tr><td>Save project</td><td>Ctrl + S</td></tr>
            <tr><td>Export code</td><td>Ctrl + E</td></tr>
        </table>

        <h3>Canvas Controls</h3>
        <table>
            <tr><th>Action</th><th>Shortcut</th></tr>
            <tr><td>Brush</td><td>B</td></tr>
            <tr><td>Eraser</td><td>E</td></tr>
            <tr><td>Clear frame</td><td>⌘ + ⌫</td></tr>
            <tr><td>Move pixels</td><td>⇧ + Arrow keys</td></tr>
            <tr><td>Move with wrap</td><td>⇧ + ⌘ + Arrow keys</td></tr>
        </table>

        <h3>Timeline Controls</h3>
        <table>
            <tr><th>Action</th><th>Shortcut</th></tr>
            <tr><td>New frame</td><td>Ctrl + N</td></tr>
            <tr><td>Duplicate frame</td><td>Ctrl + D</td></tr>
            <tr><td>Delete frame</td><td>Ctrl + ⌫</td></tr>
            <tr><td>Delete all frames</td><td>Ctrl + ⇧ + ⌫</td></tr>
            <tr><td>Move between frames</td><td>Arrow keys</td></tr>
        </table>

        <h2>File Types</h2>
        <p>The editor works with two file types:</p>
        <ul>
            <li><strong>.mpj</strong> — Working project file (save/restore your session)</li>
            <li><strong>.h</strong> — Exported animation for Arduino</li>
        </ul>

        <h2>Using Animations in Arduino</h2>
        <ol>
            <li>Export your animation as a <code>.h</code> file</li>
            <li>Copy the file to your Arduino sketch folder</li>
            <li>Include it in your sketch: <code>#include "myAnimation.h"</code></li>
            <li>Create an Animation variable: <code>Animation myAnim = animation;</code></li>
            <li>Play it: <code>screen.play(myAnim, LOOP);</code></li>
        </ol>

        <div class="info-box note">
            <strong>Important</strong>
            Do not include spaces in the file name when exporting.
        </div>

        <h2>Converting to GIF</h2>
        <p>You can convert <code>.h</code> files to animated GIFs for documentation:</p>
        <ol>
            <li>Go to the <a href="https://npuckett.github.io/gifBuilder/" target="_blank">GIF Builder</a></li>
            <li>Click "Choose File" and select your <code>.h</code> file</li>
            <li>Click "Save GIF" to download</li>
        </ol>
    `,

    'simple-led': `
        <h1>Simple LED Mode</h1>
        <p>Control individual LEDs like <code>digitalWrite()</code> — the simplest way to get started with the LED matrix.</p>

        <h2>Setup</h2>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

void setup() {
    ledBegin();    // Initialize the matrix
}</code></pre>

        <h2>Functions</h2>

        <div class="api-method">
            <h3>ledBegin()</h3>
            <p>Initialize the LED matrix. Call once in <code>setup()</code>.</p>
            <pre><code class="language-cpp">void setup() {
    ledBegin();
}</code></pre>
        </div>

        <div class="api-method">
            <h3>ledWrite(x, y, state)</h3>
            <p>Set an LED at coordinates (x, y) to HIGH or LOW.</p>
            <table>
                <tr><th>Parameter</th><th>Type</th><th>Description</th></tr>
                <tr><td>x</td><td>int</td><td>X coordinate (0-11)</td></tr>
                <tr><td>y</td><td>int</td><td>Y coordinate (0-7)</td></tr>
                <tr><td>state</td><td>int</td><td>HIGH or LOW</td></tr>
            </table>
            <pre><code class="language-cpp">ledWrite(0, 0, HIGH);    // Top-left ON
ledWrite(5, 3, LOW);     // Center OFF</code></pre>
        </div>

        <div class="api-method">
            <h3>ledWrite(index, state)</h3>
            <p>Set an LED by linear index (0-95).</p>
            <pre><code class="language-cpp">ledWrite(0, HIGH);       // First LED ON
ledWrite(95, HIGH);      // Last LED ON</code></pre>
        </div>

        <div class="api-method">
            <h3>ledRead(x, y)</h3>
            <p>Read the current state of an LED.</p>
            <p><strong>Returns:</strong> HIGH or LOW</p>
            <pre><code class="language-cpp">int state = ledRead(0, 0);
if (state == HIGH) {
    // LED is on
}</code></pre>
        </div>

        <div class="api-method">
            <h3>ledToggle(x, y)</h3>
            <p>Toggle an LED between ON and OFF.</p>
            <pre><code class="language-cpp">ledToggle(5, 3);    // If on, turn off. If off, turn on.</code></pre>
        </div>

        <div class="api-method">
            <h3>ledClear()</h3>
            <p>Turn off all LEDs.</p>
            <pre><code class="language-cpp">ledClear();    // All LEDs off</code></pre>
        </div>
    `,

    'animation-mode': `
        <h1>Animation Mode API</h1>
        <p>Play pre-made frame-by-frame animations created with the LED Matrix Editor.</p>

        <div class="gif-grid">
            <img src="../images/character.gif" alt="Character animation">
            <img src="../images/landscape.gif" alt="Landscape animation">
            <img src="../images/load.gif" alt="Loading animation">
            <img src="../images/pow.gif" alt="Pow animation">
        </div>

        <h2>Overview</h2>
        <p>Animation Mode is like a video player for the LED matrix:</p>
        <ul>
            <li><strong>Load</strong> animation frames from <code>.h</code> files</li>
            <li><strong>Play</strong> with different modes (loop, once, boomerang)</li>
            <li><strong>Control</strong> speed, pause, resume, and playback position</li>
            <li><strong>Layer</strong> multiple animations on top of each other</li>
        </ul>

        <h2>Setup</h2>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "myAnimation.h"       // From LED Matrix Editor

TinyScreen screen;
Animation anim = animation;    // 'animation' is defined in .h file

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    screen.update();           // REQUIRED - call every loop!
}</code></pre>

        <div class="info-box note">
            <strong>Important</strong>
            You must call <code>screen.update()</code> in your <code>loop()</code> function. This advances the animation frames.
        </div>

        <h2>Playback Methods</h2>

        <div class="api-method">
            <h3>play(animation, mode)</h3>
            <p>Starts playing an animation with the specified mode.</p>
            <table>
                <tr><th>Parameter</th><th>Type</th><th>Description</th></tr>
                <tr><td>animation</td><td>Animation</td><td>Animation object from .h file</td></tr>
                <tr><td>mode</td><td>PlayMode</td><td>LOOP, ONCE, or BOOMERANG</td></tr>
                <tr><td>startFrame</td><td>int</td><td>Optional: first frame (1-indexed)</td></tr>
                <tr><td>endFrame</td><td>int</td><td>Optional: last frame (1-indexed)</td></tr>
            </table>
            <pre><code class="language-cpp">screen.play(myAnim, LOOP);
screen.play(myAnim, ONCE, 2, 6);  // Play frames 2-6 once</code></pre>
        </div>

        <div class="api-method">
            <h3>pause()</h3>
            <p>Pauses the current animation at its current frame.</p>
            <pre><code class="language-cpp">screen.pause();</code></pre>
        </div>

        <div class="api-method">
            <h3>resume()</h3>
            <p>Resumes a paused animation from where it stopped.</p>
            <pre><code class="language-cpp">screen.resume();</code></pre>
        </div>

        <div class="api-method">
            <h3>stop()</h3>
            <p>Stops the animation and clears the display.</p>
            <pre><code class="language-cpp">screen.stop();</code></pre>
        </div>

        <div class="api-method">
            <h3>update()</h3>
            <p>Updates the animation. <strong>Must be called every loop.</strong></p>
            <pre><code class="language-cpp">void loop() {
    screen.update();
}</code></pre>
        </div>

        <h2>Play Modes</h2>
        <table>
            <tr><th>Mode</th><th>Description</th></tr>
            <tr><td><code>LOOP</code></td><td>Play continuously, restarting when finished</td></tr>
            <tr><td><code>ONCE</code></td><td>Play once and stop on the last frame</td></tr>
            <tr><td><code>BOOMERANG</code></td><td>Play forward, then backward (ping-pong)</td></tr>
        </table>

        <h2>Speed Control</h2>

        <div class="api-method">
            <h3>setSpeed(multiplier)</h3>
            <p>Change playback speed. 1.0 = normal, 2.0 = double speed, 0.5 = half speed.</p>
            <pre><code class="language-cpp">screen.setSpeed(2.0);     // 2x speed
screen.setSpeed(0.5);     // Half speed</code></pre>
        </div>

        <div class="api-method">
            <h3>restoreOriginalSpeed()</h3>
            <p>Reset to the original timing from the animation file.</p>
            <pre><code class="language-cpp">screen.restoreOriginalSpeed();</code></pre>
        </div>

        <div class="api-method">
            <h3>getCurrentSpeed()</h3>
            <p>Get the current speed multiplier.</p>
            <pre><code class="language-cpp">float speed = screen.getCurrentSpeed();</code></pre>
        </div>

        <h2>Status Methods</h2>
        <table>
            <tr><th>Method</th><th>Returns</th><th>Description</th></tr>
            <tr><td><code>isPlaying()</code></td><td>bool</td><td>True if animation is playing</td></tr>
            <tr><td><code>isPaused()</code></td><td>bool</td><td>True if animation is paused</td></tr>
            <tr><td><code>isComplete()</code></td><td>bool</td><td>True if ONCE mode finished</td></tr>
            <tr><td><code>getCurrentFrame()</code></td><td>int</td><td>Current frame number (1-indexed)</td></tr>
            <tr><td><code>getTotalFrames()</code></td><td>int</td><td>Total number of frames</td></tr>
        </table>

        <h2>Layered Animations</h2>
        <p>Stack multiple animations on top of each other.</p>
        <pre><code class="language-cpp">screen.begin();
screen.addLayer();                        // Add a second layer

screen.play(backgroundAnim, LOOP);        // Layer 0 (background)
screen.playOnLayer(1, foregroundAnim, LOOP);  // Layer 1 (foreground)</code></pre>

        <h3>Layer Methods</h3>
        <table>
            <tr><th>Method</th><th>Description</th></tr>
            <tr><td><code>addLayer()</code></td><td>Add a new animation layer</td></tr>
            <tr><td><code>playOnLayer(layer, anim, mode)</code></td><td>Play animation on specific layer</td></tr>
            <tr><td><code>setSpeedOnLayer(layer, speed)</code></td><td>Set speed for specific layer</td></tr>
            <tr><td><code>pauseLayer(layer)</code></td><td>Pause specific layer</td></tr>
            <tr><td><code>resumeLayer(layer)</code></td><td>Resume specific layer</td></tr>
            <tr><td><code>stopLayer(layer)</code></td><td>Stop specific layer</td></tr>
        </table>
    `,

    'canvas-mode': `
        <h1>Canvas Mode API</h1>
        <p>Draw directly to the LED matrix using code. Generate graphics in real-time.</p>

        <h2>Overview</h2>
        <p>Canvas Mode is perfect for:</p>
        <ul>
            <li><strong>Dynamic data</strong> — sensor readings, counters, progress bars</li>
            <li><strong>Procedural effects</strong> — sine waves, bouncing dots, patterns</li>
            <li><strong>Interactive graphics</strong> — responding to input in real-time</li>
        </ul>

        <div class="info-box note">
            <strong>Monochrome Matrix</strong>
            The LED matrix is on/off only — no color or brightness. Use <code>ON</code> and <code>OFF</code> constants.
        </div>

        <h2>Setup</h2>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    // Draw something here
    screen.endDraw();
}</code></pre>

        <h2>Drawing Control</h2>

        <div class="api-method">
            <h3>beginDraw() / endDraw()</h3>
            <p>Begin and end a drawing operation. All drawing commands go between these calls.</p>
            <pre><code class="language-cpp">screen.beginDraw();
screen.clear();
screen.point(5, 3);
screen.endDraw();</code></pre>
        </div>

        <div class="api-method">
            <h3>clear()</h3>
            <p>Clear the display (all LEDs off).</p>
            <pre><code class="language-cpp">screen.clear();</code></pre>
        </div>

        <div class="api-method">
            <h3>background(state)</h3>
            <p>Set the background state (ON or OFF).</p>
            <pre><code class="language-cpp">screen.background(OFF);   // Dark background
screen.background(ON);    // Lit background</code></pre>
        </div>

        <h2>Style Control</h2>

        <div class="api-method">
            <h3>stroke(state) / noStroke()</h3>
            <p>Set outline state for shapes.</p>
            <pre><code class="language-cpp">screen.stroke(ON);    // Outlines will be lit
screen.noStroke();    // No outlines</code></pre>
        </div>

        <div class="api-method">
            <h3>fill(state) / noFill()</h3>
            <p>Set fill state for shapes.</p>
            <pre><code class="language-cpp">screen.fill(ON);      // Shapes will be filled
screen.noFill();      // No fill (outline only)</code></pre>
        </div>

        <h2>Drawing Methods</h2>

        <div class="api-method">
            <h3>point(x, y)</h3>
            <p>Draw a single point.</p>
            <pre><code class="language-cpp">screen.point(5, 3);   // Point at center-ish</code></pre>
        </div>

        <div class="api-method">
            <h3>line(x1, y1, x2, y2)</h3>
            <p>Draw a line between two points.</p>
            <pre><code class="language-cpp">screen.line(0, 0, 11, 7);   // Diagonal line</code></pre>
        </div>

        <div class="api-method">
            <h3>rect(x, y, width, height)</h3>
            <p>Draw a rectangle.</p>
            <pre><code class="language-cpp">screen.rect(2, 1, 8, 6);    // Rectangle</code></pre>
        </div>

        <div class="api-method">
            <h3>circle(cx, cy, radius)</h3>
            <p>Draw a circle.</p>
            <pre><code class="language-cpp">screen.circle(5, 3, 2);     // Circle at center</code></pre>
        </div>

        <div class="api-method">
            <h3>ellipse(cx, cy, width, height)</h3>
            <p>Draw an ellipse.</p>
            <pre><code class="language-cpp">screen.ellipse(5, 3, 6, 4); // Ellipse</code></pre>
        </div>

        <h2>Text Methods</h2>

        <div class="api-method">
            <h3>text(string, x, y)</h3>
            <p>Draw text at position.</p>
            <pre><code class="language-cpp">screen.text("Hi", 0, 0);</code></pre>
        </div>

        <div class="api-method">
            <h3>textScrollSpeed(speed)</h3>
            <p>Set scroll speed for text that's wider than the display.</p>
            <pre><code class="language-cpp">screen.textScrollSpeed(100);   // 100ms per step</code></pre>
        </div>

        <h3>Scrolling Text Example</h3>
        <pre><code class="language-cpp">screen.beginDraw();

screen.stroke(ON);
screen.textScrollSpeed(100);

screen.beginText(0, 0);
screen.print("Hello World!");
screen.endText();

screen.endDraw();</code></pre>

        <h2>Matrix Info</h2>
        <table>
            <tr><th>Method</th><th>Returns</th></tr>
            <tr><td><code>width()</code></td><td>12 (matrix width)</td></tr>
            <tr><td><code>height()</code></td><td>8 (matrix height)</td></tr>
        </table>
    `,

    'hybrid-mode': `
        <h1>Hybrid Mode API</h1>
        <p>Combine animations with code-drawn elements. Draw on top of playing animations.</p>

        <h2>Overview</h2>
        <p>Hybrid Mode is perfect for:</p>
        <ul>
            <li><strong>Progress indicators</strong> on animated backgrounds</li>
            <li><strong>Sparkle/effect overlays</strong> on character animations</li>
            <li><strong>HUD elements</strong> over game backgrounds</li>
            <li><strong>Interactive highlights</strong> responding to input</li>
        </ul>

        <div class="info-box note">
            <strong>Key Difference</strong>
            <code>beginDraw()</code> clears the matrix. <code>beginOverlay()</code> preserves the current animation frame.
        </div>

        <h2>Setup</h2>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "myAnimation.h"

TinyScreen screen;
Animation anim = animation;

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    // 1. Update animation frame
    screen.update();
    
    // 2. Draw overlay on top
    screen.beginOverlay();
    screen.point(11, 0);        // Status indicator in corner
    screen.endOverlay();
}</code></pre>

        <h2>Overlay Methods</h2>

        <div class="api-method">
            <h3>beginOverlay()</h3>
            <p>Begin an overlay drawing operation. Preserves the current animation frame underneath.</p>
            <pre><code class="language-cpp">screen.beginOverlay();
// Draw on top of animation
screen.endOverlay();</code></pre>
        </div>

        <div class="api-method">
            <h3>endOverlay()</h3>
            <p>End the overlay and display the combined result.</p>
            <pre><code class="language-cpp">screen.endOverlay();</code></pre>
        </div>

        <h2>Drawing in Overlay</h2>
        <p>All Canvas Mode drawing methods work in overlay mode:</p>
        <pre><code class="language-cpp">screen.update();

screen.beginOverlay();

// Points
screen.point(x, y);

// Lines
screen.line(x1, y1, x2, y2);

// Shapes
screen.rect(x, y, w, h);
screen.circle(cx, cy, r);

screen.endOverlay();</code></pre>

        <h2>Example: Progress Bar Overlay</h2>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "loading.h"

TinyScreen screen;
Animation loadAnim = loading;
int progress = 0;

void setup() {
    screen.begin();
    screen.play(loadAnim, LOOP);
}

void loop() {
    screen.update();
    
    // Draw progress bar on bottom row
    screen.beginOverlay();
    int barWidth = map(progress, 0, 100, 0, 12);
    screen.line(0, 7, barWidth - 1, 7);
    screen.endOverlay();
    
    progress = (progress + 1) % 101;
    delay(50);
}</code></pre>
    `,

    'examples-basics': `
        <h1>Basic Examples</h1>
        <p>Simple examples to get started with the TinyFilmFestival library.</p>

        <h2>SimpleLED</h2>
        <p>The most basic example — control individual LEDs.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

void setup() {
    ledBegin();
    ledWrite(0, 0, HIGH);     // Top-left ON
}

void loop() {
    ledWrite(5, 3, HIGH);
    delay(500);
    ledWrite(5, 3, LOW);
    delay(500);
}</code></pre>

        <h2>FirstAnimation</h2>
        <p>Load and play a pre-made animation file.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "animation.h"

TinyScreen screen;
Animation myAnim = animation;

void setup() {
    screen.begin();
    screen.play(myAnim, LOOP);
}

void loop() {
    screen.update();
}</code></pre>

        <h2>FirstCanvas</h2>
        <p>Draw graphics with code.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    screen.stroke(ON);
    screen.line(0, 0, 11, 7);
    screen.endDraw();
    delay(100);
}</code></pre>
    `,

    'examples-animation': `
        <h1>Animation Mode Examples</h1>

        <h2>LayeredAnimations</h2>
        <p>Stack multiple animations on different layers.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "landscape.h"
#include "fiz.h"

TinyScreen screen;
Animation bgAnim = landscape;
Animation fgAnim = fiz;

void setup() {
    screen.begin();
    screen.addLayer();
    
    screen.play(bgAnim, LOOP);
    screen.playOnLayer(1, fgAnim, LOOP);
}

void loop() {
    screen.update();
}</code></pre>

        <h2>PlaybackControl</h2>
        <p>Control animation playback — pause, resume, change speed.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "animation.h"

TinyScreen screen;
Animation anim = animation;

void setup() {
    Serial.begin(9600);
    screen.begin();
    screen.play(anim, LOOP);
    
    Serial.println("Commands: p=pause, r=resume, +=faster, -=slower");
}

void loop() {
    screen.update();
    
    if (Serial.available()) {
        char c = Serial.read();
        
        switch (c) {
            case 'p': screen.pause(); break;
            case 'r': screen.resume(); break;
            case '+': screen.setSpeed(screen.getCurrentSpeed() + 0.5); break;
            case '-': screen.setSpeed(max(0.1, screen.getCurrentSpeed() - 0.5)); break;
        }
    }
}</code></pre>
    `,

    'examples-canvas': `
        <h1>Canvas Mode Examples</h1>

        <h2>ScrollingText</h2>
        <p>Display scrolling text on the matrix.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.stroke(ON);
    screen.textScrollSpeed(100);
    
    screen.beginText(0, 0);
    screen.print("Hello World!");
    screen.endText();
    
    screen.endDraw();
}</code></pre>

        <h2>MovingShapes</h2>
        <p>Animate shapes moving across the display.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;
int x = 0;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    screen.stroke(ON);
    screen.noFill();
    screen.circle(x, 3, 2);
    
    screen.endDraw();
    
    x = (x + 1) % 12;
    delay(100);
}</code></pre>

        <h2>LayeredGraphics</h2>
        <p>Draw multiple layers of graphics.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    // Background pattern
    for (int i = 0; i < 12; i += 2) {
        screen.point(i, 7);
    }
    
    // Moving foreground
    static int pos = 0;
    screen.rect(pos, 2, 3, 3);
    pos = (pos + 1) % 10;
    
    screen.endDraw();
    delay(150);
}</code></pre>
    `,

    'examples-hybrid': `
        <h1>Hybrid Mode Examples</h1>

        <h2>AnimationWithOverlay</h2>
        <p>Draw dynamic content over a playing animation.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "landscape.h"

TinyScreen screen;
Animation bgAnim = landscape;

void setup() {
    screen.begin();
    screen.play(bgAnim, LOOP);
}

void loop() {
    screen.update();
    
    // Draw blinking indicator
    screen.beginOverlay();
    if ((millis() / 500) % 2 == 0) {
        screen.point(11, 0);
    }
    screen.endOverlay();
}</code></pre>

        <h2>Progress Bar Over Animation</h2>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;
int progress = 0;

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    screen.update();
    
    screen.beginOverlay();
    int barWidth = map(progress, 0, 100, 0, 12);
    for (int x = 0; x < barWidth; x++) {
        screen.point(x, 7);
    }
    screen.endOverlay();
    
    progress = (progress + 1) % 101;
    delay(50);
}</code></pre>
    `,

    'examples-sensors': `
        <h1>Sensor Control Examples</h1>
        <p>Control animations with buttons and sensors.</p>

        <h2>Button Play/Pause</h2>
        <p>Use a button to pause and resume an animation.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;

const int buttonPin = 2;
bool lastState = HIGH;
bool paused = false;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    bool state = digitalRead(buttonPin);
    
    // Button pressed (falling edge)
    if (state == LOW && lastState == HIGH) {
        if (paused) {
            screen.resume();
            paused = false;
        } else {
            screen.pause();
            paused = true;
        }
    }
    
    lastState = state;
    screen.update();
}</code></pre>

        <h2>Button Content Switch</h2>
        <p>Switch between animations with a button.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

TinyScreen screen;
Animation idleAnim = idle;
Animation goAnim = go;

const int buttonPin = 2;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    screen.begin();
    screen.play(idleAnim, LOOP);
}

void loop() {
    bool pressed = (digitalRead(buttonPin) == LOW);
    
    static bool wasPressed = false;
    if (pressed && !wasPressed) {
        screen.play(goAnim, LOOP);
    } else if (!pressed && wasPressed) {
        screen.play(idleAnim, LOOP);
    }
    wasPressed = pressed;
    
    screen.update();
}</code></pre>

        <h2>Distance Speed Control</h2>
        <p>Control animation speed with a distance sensor.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;

const int trigPin = 9;
const int echoPin = 10;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    // Measure distance
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;  // cm
    
    // Map distance to speed (closer = faster)
    float speed = map(constrain(distance, 5, 50), 5, 50, 30, 5) / 10.0;
    screen.setSpeed(speed);
    
    screen.update();
}</code></pre>
    `,

    'examples-utilities': `
        <h1>Utility Examples</h1>

        <h2>EaseDemo</h2>
        <p>Demonstrate easing functions for smooth animations.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

// Simple ease-in-out function
float easeInOut(float t) {
    return t < 0.5 
        ? 2 * t * t 
        : 1 - pow(-2 * t + 2, 2) / 2;
}

void loop() {
    static float t = 0;
    
    screen.beginDraw();
    screen.clear();
    
    float eased = easeInOut(t);
    int x = eased * 11;
    screen.point(x, 3);
    
    screen.endDraw();
    
    t += 0.02;
    if (t > 1) t = 0;
    
    delay(20);
}</code></pre>

        <h2>OscillatorDemo</h2>
        <p>Use sine waves for oscillating animations.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    // Draw sine wave
    for (int x = 0; x < 12; x++) {
        float phase = millis() / 200.0;
        int y = 3 + sin(x * 0.5 + phase) * 3;
        screen.point(x, y);
    }
    
    screen.endDraw();
    delay(30);
}</code></pre>

        <h2>SmoothAnimation</h2>
        <p>Create smooth motion using interpolation.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

float currentX = 0;
float targetX = 11;
float smoothing = 0.1;

void setup() {
    screen.begin();
}

void loop() {
    // Smooth interpolation toward target
    currentX += (targetX - currentX) * smoothing;
    
    screen.beginDraw();
    screen.clear();
    screen.point((int)currentX, 3);
    screen.endDraw();
    
    // Switch direction when close to target
    if (abs(currentX - targetX) < 0.1) {
        targetX = (targetX > 5) ? 0 : 11;
    }
    
    delay(30);
}</code></pre>
    `,

    'deprecated': `
        <h1>V1 Deprecated Methods</h1>
        <p>These V1.x methods are still supported for backward compatibility but are deprecated in V2.0. New projects should use the V2 <code>TinyScreen</code> API.</p>

        <h2>Class Aliases</h2>

        <h3>TinyFilmFestival</h3>
        <p>Deprecated alias for <code>TinyScreen</code>.</p>
        <pre><code class="language-cpp">// V1 (still works)
TinyFilmFestival film;

// V2 (recommended)
TinyScreen screen;</code></pre>

        <h3>CombinedFilmFestival</h3>
        <p>Deprecated — use <code>TinyScreen</code> with <code>addLayer()</code> instead.</p>
        <pre><code class="language-cpp">// V1 (still works)
TinyFilmFestival bg, fg;
CombinedFilmFestival combined;

combined.begin();
bg.startAnimation(bgAnim, LOOP);
fg.startAnimation(fgAnim, LOOP);
combined.addFilm(bg);
combined.addFilm(fg);

// V2 (recommended)
TinyScreen screen;

screen.begin();
screen.addLayer();
screen.play(bgAnim, LOOP);
screen.playOnLayer(1, fgAnim, LOOP);</code></pre>

        <h2>Deprecated Methods</h2>

        <h3>startAnimation()</h3>
        <p>Deprecated — use <code>play()</code> instead.</p>
        <pre><code class="language-cpp">// V1 (still works)
film.startAnimation(myAnim, LOOP);
film.startAnimation(myAnim, LOOP, 2, 6);

// V2 (recommended)
screen.play(myAnim, LOOP);
screen.play(myAnim, LOOP, 2, 6);</code></pre>

        <h2>PlayMode Constants</h2>
        <p>Both naming styles work:</p>
        <table>
            <tr><th>V1 Constant</th><th>V2 Constant</th><th>Description</th></tr>
            <tr><td><code>PLAY_ONCE</code></td><td><code>ONCE</code></td><td>Play once and stop</td></tr>
            <tr><td><code>PLAY_LOOP</code></td><td><code>LOOP</code></td><td>Loop continuously</td></tr>
            <tr><td><code>PLAY_BOOMERANG</code></td><td><code>BOOMERANG</code></td><td>Ping-pong</td></tr>
        </table>
    `,

    // Individual Examples - Basics
    'example-simple-led': `
        <h1>SimpleLED Example</h1>
        <p class="example-breadcrumb">Examples → Basics → SimpleLED</p>
        <p>The most basic example — control individual LEDs like <code>digitalWrite()</code>.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

void setup() {
    ledBegin();                   // Initialize matrix
    
    ledWrite(0, 0, HIGH);         // Top-left ON
    ledWrite(11, 7, HIGH);        // Bottom-right ON
    ledToggle(0, 0);              // Toggle top-left OFF
}

void loop() {
    ledWrite(5, 3, HIGH);         // Center ON
    delay(500);
    ledWrite(5, 3, LOW);          // Center OFF
    delay(500);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Initializing the LED matrix with <code>ledBegin()</code></li>
            <li>Turning LEDs on/off with <code>ledWrite()</code></li>
            <li>Using <code>ledToggle()</code> to flip LED state</li>
            <li>Coordinate system: (0,0) is top-left, (11,7) is bottom-right</li>
        </ul>
    `,

    'example-first-animation': `
        <h1>FirstAnimation Example</h1>
        <p class="example-breadcrumb">Examples → Basics → FirstAnimation</p>
        <p>Load and play a pre-made animation file from the LED Matrix Editor.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "animation.h"

TinyScreen screen;
Animation myAnim = animation;

void setup() {
    screen.begin();
    
    // Play animation in a loop
    // Try also: ONCE (play once) or BOOMERANG (forward/backward)
    screen.play(myAnim, LOOP);
}

void loop() {
    screen.update();
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Including an animation <code>.h</code> file</li>
            <li>Creating a <code>TinyScreen</code> object</li>
            <li>Wrapping raw animation data in an <code>Animation</code> object</li>
            <li>Playing with <code>LOOP</code> mode</li>
            <li>Calling <code>update()</code> every loop</li>
        </ul>
    `,

    'example-first-canvas': `
        <h1>FirstCanvas Example</h1>
        <p class="example-breadcrumb">Examples → Basics → FirstCanvas</p>
        <p>Draw graphics with code using Processing-style commands.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    screen.stroke(ON);
    screen.line(0, 0, 11, 7);     // Diagonal line
    
    screen.endDraw();
    delay(100);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Using <code>beginDraw()</code> and <code>endDraw()</code></li>
            <li>Clearing the display with <code>clear()</code></li>
            <li>Setting stroke state with <code>stroke(ON)</code></li>
            <li>Drawing a line between two points</li>
        </ul>
    `,

    // Individual Examples - Animation Mode
    'example-layered-animations': `
        <h1>LayeredAnimations Example</h1>
        <p class="example-breadcrumb">Examples → Animation Mode → LayeredAnimations</p>
        <p>Stack multiple animations on different layers for complex visual effects.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "landscape.h"
#include "fiz.h"

TinyScreen screen;
Animation bgAnim = landscape;
Animation fgAnim = fiz;

void setup() {
    screen.begin();
    screen.addLayer();                        // Add layer 1
    
    screen.play(bgAnim, LOOP);                // Layer 0 (background)
    screen.playOnLayer(1, fgAnim, LOOP);      // Layer 1 (foreground)
}

void loop() {
    screen.update();
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Adding animation layers with <code>addLayer()</code></li>
            <li>Playing animations on specific layers</li>
            <li>Layer 0 is the background, higher layers render on top</li>
            <li>Each layer can have independent speed and playback control</li>
        </ul>
    `,

    'example-playback-control': `
        <h1>PlaybackControl Example</h1>
        <p class="example-breadcrumb">Examples → Animation Mode → PlaybackControl</p>
        <p>Control animation playback via Serial commands — pause, resume, change speed.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "animation.h"

TinyScreen screen;
Animation anim = animation;

void setup() {
    Serial.begin(9600);
    screen.begin();
    screen.play(anim, LOOP);
    
    Serial.println("Commands: p=pause, r=resume, +=faster, -=slower");
}

void loop() {
    screen.update();
    
    if (Serial.available()) {
        char c = Serial.read();
        
        switch (c) {
            case 'p': screen.pause(); break;
            case 'r': screen.resume(); break;
            case '+': screen.setSpeed(screen.getCurrentSpeed() + 0.5); break;
            case '-': screen.setSpeed(max(0.1, screen.getCurrentSpeed() - 0.5)); break;
        }
    }
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Pausing and resuming animations</li>
            <li>Dynamically changing playback speed</li>
            <li>Reading current speed with <code>getCurrentSpeed()</code></li>
            <li>Serial communication for debugging</li>
        </ul>
    `,

    // Individual Examples - Canvas Mode
    'example-scrolling-text': `
        <h1>ScrollingText Example</h1>
        <p class="example-breadcrumb">Examples → Canvas Mode → ScrollingText</p>
        <p>Display scrolling text across the LED matrix.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    
    screen.stroke(ON);
    screen.textScrollSpeed(100);
    
    screen.beginText(0, 0);
    screen.print("Hello World!");
    screen.endText();
    
    screen.endDraw();
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Using text drawing methods</li>
            <li>Setting scroll speed with <code>textScrollSpeed()</code></li>
            <li>Using <code>beginText()</code> and <code>endText()</code> for text blocks</li>
            <li>Text automatically scrolls when wider than display</li>
        </ul>
    `,

    'example-moving-shapes': `
        <h1>MovingShapes Example</h1>
        <p class="example-breadcrumb">Examples → Canvas Mode → MovingShapes</p>
        <p>Animate shapes moving across the display.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;
int x = 0;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    screen.stroke(ON);
    screen.noFill();
    screen.circle(x, 3, 2);
    
    screen.endDraw();
    
    x = (x + 1) % 12;
    delay(100);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Creating animated graphics with code</li>
            <li>Using <code>circle()</code> to draw circles</li>
            <li>Using <code>noFill()</code> for outline-only shapes</li>
            <li>Wrapping position with modulo operator</li>
        </ul>
    `,

    'example-layered-graphics': `
        <h1>LayeredGraphics Example</h1>
        <p class="example-breadcrumb">Examples → Canvas Mode → LayeredGraphics</p>
        <p>Draw multiple layers of graphics in a single frame.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    // Background pattern
    for (int i = 0; i < 12; i += 2) {
        screen.point(i, 7);
    }
    
    // Moving foreground
    static int pos = 0;
    screen.rect(pos, 2, 3, 3);
    pos = (pos + 1) % 10;
    
    screen.endDraw();
    delay(150);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Drawing multiple elements in one frame</li>
            <li>Using loops to create patterns</li>
            <li>Combining static and animated elements</li>
            <li>Using <code>static</code> variables for persistence</li>
        </ul>
    `,

    // Individual Examples - Hybrid Mode
    'example-animation-overlay': `
        <h1>AnimationWithOverlay Example</h1>
        <p class="example-breadcrumb">Examples → Hybrid Mode → AnimationWithOverlay</p>
        <p>Draw dynamic content over a playing animation.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "landscape.h"

TinyScreen screen;
Animation bgAnim = landscape;

void setup() {
    screen.begin();
    screen.play(bgAnim, LOOP);
}

void loop() {
    screen.update();
    
    // Draw blinking indicator over animation
    screen.beginOverlay();
    if ((millis() / 500) % 2 == 0) {
        screen.point(11, 0);
    }
    screen.endOverlay();
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Using <code>beginOverlay()</code> instead of <code>beginDraw()</code></li>
            <li>Overlay preserves the animation frame underneath</li>
            <li>Creating blinking effects with <code>millis()</code></li>
            <li>Combining pre-made animations with dynamic elements</li>
        </ul>
    `,

    // Individual Examples - Sensor Control
    'example-button-play-pause': `
        <h1>Button_PlayPause Example</h1>
        <p class="example-breadcrumb">Examples → Sensor Control → Button_PlayPause</p>
        <p>Use a button to pause and resume an animation.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;

const int buttonPin = 2;
bool lastState = HIGH;
bool paused = false;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    bool state = digitalRead(buttonPin);
    
    // Button pressed (falling edge)
    if (state == LOW && lastState == HIGH) {
        if (paused) {
            screen.resume();
            paused = false;
        } else {
            screen.pause();
            paused = true;
        }
    }
    
    lastState = state;
    screen.update();
}</code></pre>
        <h2>Hardware Required</h2>
        <ul>
            <li>Arduino UNO R4 WiFi</li>
            <li>Pushbutton connected to pin 2 and GND</li>
        </ul>
    `,

    'example-button-content-switch': `
        <h1>Button_ContentSwitch Example</h1>
        <p class="example-breadcrumb">Examples → Sensor Control → Button_ContentSwitch</p>
        <p>Switch between two animations based on button state.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

TinyScreen screen;
Animation idleAnim = idle;
Animation goAnim = go;

const int buttonPin = 2;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    screen.begin();
    screen.play(idleAnim, LOOP);
}

void loop() {
    bool pressed = (digitalRead(buttonPin) == LOW);
    
    static bool wasPressed = false;
    if (pressed && !wasPressed) {
        screen.play(goAnim, LOOP);
    } else if (!pressed && wasPressed) {
        screen.play(idleAnim, LOOP);
    }
    wasPressed = pressed;
    
    screen.update();
}</code></pre>
        <h2>Hardware Required</h2>
        <ul>
            <li>Arduino UNO R4 WiFi</li>
            <li>Pushbutton connected to pin 2 and GND</li>
        </ul>
    `,

    'example-distance-speed': `
        <h1>Distance_SpeedControl Example</h1>
        <p class="example-breadcrumb">Examples → Sensor Control → Distance_SpeedControl</p>
        <p>Control animation speed with an ultrasonic distance sensor.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;

const int trigPin = 9;
const int echoPin = 10;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    // Measure distance
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;  // cm
    
    // Map distance to speed (closer = faster)
    float speed = map(constrain(distance, 5, 50), 5, 50, 30, 5) / 10.0;
    screen.setSpeed(speed);
    
    screen.update();
}</code></pre>
        <h2>Hardware Required</h2>
        <ul>
            <li>Arduino UNO R4 WiFi</li>
            <li>HC-SR04 ultrasonic sensor (trig on pin 9, echo on pin 10)</li>
        </ul>
    `,

    'example-distance-zone': `
        <h1>Distance_ZoneSwitch Example</h1>
        <p class="example-breadcrumb">Examples → Sensor Control → Distance_ZoneSwitch</p>
        <p>Switch animations based on distance zones.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"
#include "go.h"

TinyScreen screen;
Animation idleAnim = idle;
Animation goAnim = go;

const int trigPin = 9;
const int echoPin = 10;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    screen.begin();
    screen.play(idleAnim, LOOP);
}

void loop() {
    int distance = measureDistance();
    
    static bool wasClose = false;
    bool isClose = (distance < 30);
    
    if (isClose && !wasClose) {
        screen.play(goAnim, LOOP);
    } else if (!isClose && wasClose) {
        screen.play(idleAnim, LOOP);
    }
    wasClose = isClose;
    
    screen.update();
}

int measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return pulseIn(echoPin, HIGH) * 0.034 / 2;
}</code></pre>
        <h2>Hardware Required</h2>
        <ul>
            <li>Arduino UNO R4 WiFi</li>
            <li>HC-SR04 ultrasonic sensor</li>
        </ul>
    `,

    'example-pressure-speed': `
        <h1>Pressure_SpeedControl Example</h1>
        <p class="example-breadcrumb">Examples → Sensor Control → Pressure_SpeedControl</p>
        <p>Control animation speed with a pressure/force sensor.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"
#include "idle.h"

TinyScreen screen;
Animation anim = idle;

const int pressurePin = A0;

void setup() {
    screen.begin();
    screen.play(anim, LOOP);
}

void loop() {
    int pressure = analogRead(pressurePin);
    
    // Map pressure to speed (more pressure = faster)
    float speed = map(pressure, 0, 1023, 5, 30) / 10.0;
    screen.setSpeed(speed);
    
    screen.update();
}</code></pre>
        <h2>Hardware Required</h2>
        <ul>
            <li>Arduino UNO R4 WiFi</li>
            <li>FSR (Force Sensitive Resistor) on analog pin A0</li>
            <li>10K pull-down resistor</li>
        </ul>
    `,

    // Individual Examples - Utilities
    'example-ease-demo': `
        <h1>EaseDemo Example</h1>
        <p class="example-breadcrumb">Examples → Utilities → EaseDemo</p>
        <p>Demonstrate easing functions for smooth animations.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

// Simple ease-in-out function
float easeInOut(float t) {
    return t < 0.5 
        ? 2 * t * t 
        : 1 - pow(-2 * t + 2, 2) / 2;
}

void loop() {
    static float t = 0;
    
    screen.beginDraw();
    screen.clear();
    
    float eased = easeInOut(t);
    int x = eased * 11;
    screen.point(x, 3);
    
    screen.endDraw();
    
    t += 0.02;
    if (t > 1) t = 0;
    
    delay(20);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Using mathematical easing functions</li>
            <li>Creating smooth, non-linear motion</li>
            <li>Normalizing time to 0-1 range</li>
        </ul>
    `,

    'example-oscillator-demo': `
        <h1>OscillatorDemo Example</h1>
        <p class="example-breadcrumb">Examples → Utilities → OscillatorDemo</p>
        <p>Use sine waves for oscillating animations.</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

void setup() {
    screen.begin();
}

void loop() {
    screen.beginDraw();
    screen.clear();
    
    // Draw sine wave
    for (int x = 0; x < 12; x++) {
        float phase = millis() / 200.0;
        int y = 3 + sin(x * 0.5 + phase) * 3;
        screen.point(x, y);
    }
    
    screen.endDraw();
    delay(30);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Using <code>sin()</code> for wave patterns</li>
            <li>Time-based animation with <code>millis()</code></li>
            <li>Creating organic, flowing motion</li>
        </ul>
    `,

    'example-smooth-animation': `
        <h1>SmoothAnimation Example</h1>
        <p class="example-breadcrumb">Examples → Utilities → SmoothAnimation</p>
        <p>Create smooth motion using linear interpolation (lerp).</p>
        <pre><code class="language-cpp">#include "TinyFilmFestival.h"

TinyScreen screen;

float currentX = 0;
float targetX = 11;
float smoothing = 0.1;

void setup() {
    screen.begin();
}

void loop() {
    // Smooth interpolation toward target
    currentX += (targetX - currentX) * smoothing;
    
    screen.beginDraw();
    screen.clear();
    screen.point((int)currentX, 3);
    screen.endDraw();
    
    // Switch direction when close to target
    if (abs(currentX - targetX) < 0.1) {
        targetX = (targetX > 5) ? 0 : 11;
    }
    
    delay(30);
}</code></pre>
        <h2>What This Demonstrates</h2>
        <ul>
            <li>Linear interpolation (lerp) for smooth movement</li>
            <li>Using a smoothing factor to control speed</li>
            <li>Detecting when target is reached</li>
            <li>Creating "eased" motion without explicit easing functions</li>
        </ul>
    `
};
