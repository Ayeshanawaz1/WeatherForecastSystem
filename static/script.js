document.addEventListener('DOMContentLoaded', function() {
    let searchHistory = JSON.parse(localStorage.getItem('weatherSearchHistory')) || [];
    
    // Page elements
    const welcomePage = document.getElementById('welcome-page');
    const searchPage = document.getElementById('search-page');
    const resultsPage = document.getElementById('results-page');
    const historyPage = document.getElementById('history-page');
    
    // Buttons
    const welcomeBtn = document.getElementById('welcome-btn');
    const historyBtn = document.getElementById('history-btn');
    const searchBackBtn = document.getElementById('search-back-btn');
    const resultsBackBtn = document.getElementById('results-back-btn');
    const historyBackBtn = document.getElementById('history-back-btn');
    
    // Form elements
    const cityInput = document.getElementById('city');
    const countryInput = document.getElementById('country');
    const dailyBtn = document.getElementById('daily-btn');
    const hourlyBtn = document.getElementById('hourly-btn');
    const weeklyBtn = document.getElementById('weekly-btn');
    const dateSelection = document.getElementById('date-selection');
    const dateInput = document.getElementById('date-input');
    const submitDate = document.getElementById('submit-date');
    
    // Results containers
    const weatherResults = document.getElementById('weather-results');
    const historyList = document.getElementById('history-list');
    
    // Forecast buttons
    const forecastButtons = document.querySelectorAll('.forecast-options button');

    // Set default date to today
    const today = new Date().toISOString().split('T')[0];
    dateInput.value = today;
    dateInput.min = today;

    // Initialize - show only welcome page
    showPage('welcome');

    // Navigation functions
    function showPage(page) {
        // Hide all pages
        [welcomePage, searchPage, resultsPage, historyPage].forEach(p => p.classList.remove('active'));
        
        // Show the requested page
        switch(page) {
            case 'welcome':
                welcomePage.classList.add('active');
                break;
            case 'search':
                searchPage.classList.add('active');
                break;
            case 'results':
                resultsPage.classList.add('active');
                break;
            case 'history':
                historyPage.classList.add('active');
                displayHistory();
                break;
        }
    }

    // Navigation event listeners
    welcomeBtn.addEventListener('click', () => showPage('search'));
    searchBackBtn.addEventListener('click', () => showPage('welcome'));
    resultsBackBtn.addEventListener('click', () => showPage('search'));
    historyBtn.addEventListener('click', () => showPage('history'));
    historyBackBtn.addEventListener('click', () => showPage('welcome'));

    // History functions
    function addToHistory(city, country, type, date = '') {
        const searchEntry = {
            city,
            country,
            type,
            date,
            timestamp: new Date().toISOString()
        };
        
        // Add to beginning of array (most recent first)
        searchHistory.unshift(searchEntry);
        
        // Keep only the last 10 searches
        if (searchHistory.length > 20) {
            searchHistory = searchHistory.slice(0, 20);
        }
        
        localStorage.setItem('weatherSearchHistory', JSON.stringify(searchHistory));
    }

    function displayHistory() {
    if (searchHistory.length === 0) {
        historyList.innerHTML = '<p class="empty-message">No search history yet.</p>';
        return;
    }
    
    let html = '<ul>';
    searchHistory.forEach((entry, index) => {
        let displayText = `${entry.city}, ${entry.country} - ${entry.type}`;
        if (entry.date) {
            displayText += ` (${entry.date})`;
        }
        
        html += `
            <li>
                <span>${displayText}</span>
                <div>
                    <button class="history-item-btn" data-index="${index}">Search Again</button>
                    <button class="delete-history-btn" data-index="${index}">×</button>
                </div>
            </li>
        `;
    });
    html += '</ul>';
    
    historyList.innerHTML = html;
    
    // Add event listeners to history item buttons
    document.querySelectorAll('.history-item-btn').forEach(button => {
        button.addEventListener('click', function() {
            const index = this.dataset.index;
            const entry = searchHistory[index];
            
            cityInput.value = entry.city;
            countryInput.value = entry.country;
            
            if (entry.type === 'daily') {
                dailyBtn.click();
                if (entry.date) {
                    dateInput.value = entry.date;
                }
            } 
            else if (entry.type === 'hourly') {
                hourlyBtn.click();
                if (entry.date) {
                    dateInput.value = entry.date;
                }
            } 
            else if (entry.type === 'weekly') {
                weeklyBtn.click();
            }
            
            showPage('search');
        });
    });
        
        // Add event listeners to delete buttons
        document.querySelectorAll('.delete-history-btn').forEach(button => {
        button.addEventListener('click', function() {
            const index = this.dataset.index;
            searchHistory.splice(index, 1);
            localStorage.setItem('weatherSearchHistory', JSON.stringify(searchHistory));
            displayHistory();
        });
    });
}

    // Forecast type selection
    dailyBtn.addEventListener('click', () => showDateSelection('daily'));
    hourlyBtn.addEventListener('click', () => showDateSelection('hourly'));
    weeklyBtn.addEventListener('click', () => fetchWeather('weekly'));

    submitDate.addEventListener('click', function() {
        const type = this.dataset.type;
        fetchWeather(type);
    });

    forecastButtons.forEach(button => {
        button.addEventListener('click', function() {
            forecastButtons.forEach(btn => btn.classList.remove('active'));
            this.classList.add('active');
        });
    });

    function showDateSelection(type) {
        const city = cityInput.value.trim();
        const country = countryInput.value.trim();
        
        if (!city || !country) {
            alert('Please enter both city and country');
            return;
        }
        
        submitDate.dataset.type = type;
        dateSelection.classList.remove('hidden');
        forecastButtons.forEach(btn => btn.classList.remove('active'));
        if (type === 'daily') dailyBtn.classList.add('active');
        if (type === 'hourly') hourlyBtn.classList.add('active');
    }

    function fetchWeather(type) {
    const city = cityInput.value.trim();
    const country = countryInput.value.trim();
    const date = (type === 'weekly') ? '' : dateInput.value;

    if (!city || !country) {
        alert('Please enter both city and country');
        return;
    }

    if ((type === 'daily' || type === 'hourly') && !date) {
        alert('Please select a date');
        return;
    }

    addToHistory(city, country, type, date);

    forecastButtons.forEach(btn => btn.classList.remove('active'));
    if (type === 'daily') dailyBtn.classList.add('active');
    if (type === 'hourly') hourlyBtn.classList.add('active');
    if (type === 'weekly') weeklyBtn.classList.add('active');

    showPage('results');
    dateSelection.classList.add('hidden');

    weatherResults.innerHTML = '<p>Loading weather data...</p>';

    const params = new URLSearchParams();
    params.append('city', city);
    params.append('country', country);
    params.append('type', type);

    if (date) {
        params.append('date', date);
    }

    // Make API call to the C++ backend
    fetch(`http://localhost:8080/api/weather?${params.toString()}`)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            return response.json();
        })
        .then(data => {
            if (data.error) {
                weatherResults.innerHTML = `<p class="error">${data.error}</p>`;
                return;
            }

            // Save to history
            addToHistory(city, country, type, date);

            // Display results
            displayWeatherResults(data, type);
        })
        .catch(error => {
            weatherResults.innerHTML = `<p class="error">Error fetching weather data: ${error.message}</p>`;
        });
}


    function displayWeatherResults(data, type) {
        let html = `<h2>${type.charAt(0).toUpperCase() + type.slice(1)} Forecast for ${data.city}, ${data.country}</h2>`;
        
        if (type === 'daily') {
            const isDay = isDayTime(data.date);
            html += `
                <div class="weather-card">
                    <h3>${data.date}</h3>
                    <p><strong>Temperature:</strong> ${Math.round(data.temperature)}°C</p>
                    <p><strong>Condition:</strong> ${data.condition}</p>
                    <p><strong>Humidity:</strong> ${data.humidity}%</p>
                    <p><strong>Wind Speed:</strong> ${data.windSpeed.toFixed(1)} km/h</p>
                    <div class="weather-icon-card">${getWeatherIcon(data.condition, isDay)}</div>
                </div>
            `;
        } 
        else if (type === 'hourly') {
            html += `<div class="hourly-forecast">`;
            data.hourly.forEach(hour => {
                const isDay = isDayTime(hour.time);
                html += `
                    <div class="weather-card">
                        <h3>${hour.time}</h3>
                        <p><strong>Temp:</strong> ${Math.round(hour.temperature)}°C</p>
                        <p><strong>Condition:</strong> ${hour.condition}</p>
                        <p><strong>Wind:</strong> ${hour.windSpeed.toFixed(1)} km/h</p>
                        <div class="weather-icon-card">${getWeatherIcon(hour.condition, isDay)}</div>
                    </div>
                `;
            });
            html += `</div>`;
        } 
        else if (type === 'weekly') {
            html += `<div class="weekly-forecast">`;
            data.forecast.forEach(day => {
                const isDay = true;
                html += `
                    <div class="weather-card">
                        <h3><u>${day.date}</u></h3>
                        <p><strong>Temperature:</strong> ${Math.round(day.temperature)}°C</p>
                        <p><strong>Condition:</strong> ${day.condition}</p>
                        <p><strong>Humidity:</strong> ${day.humidity}%</p>
                        <p><strong>Wind Speed:</strong> ${day.windSpeed.toFixed(1)} km/h</p>
                        <div class="weather-icon-card">${getWeatherIcon(day.condition, isDay)}</div>
                    </div>
                `;
            });
            html += `</div>`;
        }
        weatherResults.innerHTML = html;
    }

    function isDayTime(time) {
        const hour = new Date(time).getHours();
        return hour >= 6 && hour < 18; // Daytime is considered from 6 AM to 6 PM
    }

    function getWeatherIcon(condition, isDay) {
        condition = condition.toLowerCase();
        
        if (condition.includes('sun') || condition.includes('clear')) {
            return isDay ? '<i class="fas fa-sun"></i>' : '<i class="fas fa-moon"></i>';
        }
        if (condition.includes('cloud')) {
            return isDay ? '<i class="fas fa-cloud-sun"></i>' : '<i class="fas fa-cloud-moon"></i>';
        }
        if (condition.includes('rain') || condition.includes('drizzle')) {
            return '<i class="fas fa-cloud-rain"></i>';
        }
        if (condition.includes('thunder') || condition.includes('storm')) {
            return '<i class="fas fa-bolt"></i>';
        }
        if (condition.includes('snow') || condition.includes('flurr')) {
            return '<i class="far fa-snowflake"></i>';
        }
        if (condition.includes('fog') || condition.includes('mist') || condition.includes('haze')) {
            return '<i class="fas fa-smog"></i>';
        }
        return '<i class="fas fa-cloud"></i>';
    }


});