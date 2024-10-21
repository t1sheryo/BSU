const { dialog } = require('electron');
const fs = require('fs');
const jpeg = require('jpeg-js');
const pngjs = require('pngjs').PNG;
const bmp = require('bmp-js');
const tiff = require('utif');
const exif = require('exif-js');  // Для работы с EXIF

// Добавляем обработчик для input элемента
document.getElementById('fileInput').addEventListener('change', handleFileSelect);

// Обработка выбора файлов
function handleFileSelect(event) {
    const files = event.target.files;
    const tableBody = document.getElementById('tableBody');
    tableBody.innerHTML = ''; // Очищаем таблицу перед загрузкой новых файлов

    Array.from(files).forEach(file => {
        const fileName = file.name;
        const reader = new FileReader();

        reader.onload = function(e) {
            const fileType = file.type;

            if (fileType.match('image/jpeg')) {
                handleJPEG(file, fileName);
            } else if (fileType.match('image/png')) {
                handlePNG(file, fileName);
            } else if (fileType.match('image/gif')) {
                handleGIF(file, fileName);
            } else if (fileType.match('image/bmp')) {
                handleBMP(file, fileName);
            } else if (fileType.match('image/tiff')) {
                handleTIFF(file, fileName);
            } else {
                console.log('Unsupported file type: ', fileType);
            }
        };

        reader.readAsArrayBuffer(file);
    });
}

// Функция для добавления строки в таблицу с информацией об изображении
function addRowToTable(fileInfo) {
    const tableBody = document.getElementById('tableBody');
    const row = document.createElement('tr');

    const fileNameCell = document.createElement('td');
    fileNameCell.textContent = fileInfo.name;
    row.appendChild(fileNameCell);

    const dimensionsCell = document.createElement('td');
    dimensionsCell.textContent = fileInfo.dimensions;
    row.appendChild(dimensionsCell);

    const resolutionCell = document.createElement('td');
    resolutionCell.textContent = fileInfo.resolution;
    row.appendChild(resolutionCell);

    const colorDepthCell = document.createElement('td');
    colorDepthCell.textContent = fileInfo.colorDepth;
    row.appendChild(colorDepthCell);

    const compressionCell = document.createElement('td');
    compressionCell.textContent = fileInfo.compression;
    row.appendChild(compressionCell);

    tableBody.appendChild(row);
}

// Обработка файлов JPEG
function handleJPEG(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = event.target.result;
        const jpegData = jpeg.decode(new Uint8Array(data), true);

        let resolution = 'N/A'; // По умолчанию N/A
        try {
            const exifData = exif.readFromBinaryFile(data.buffer);
            if (exifData && exifData.XResolution && exifData.YResolution) {
                resolution = `${exifData.XResolution}x${exifData.YResolution} dpi`;
            }
        } catch (err) {
            console.log('No EXIF data for resolution.');
        }

        const fileInfo = {
            name: fileName,
            dimensions: `${jpegData.width}x${jpegData.height}`,
            resolution: resolution,
            colorDepth: jpegData.components * 8, // 8 бит на компонент (например, RGB = 24 бит)
            compression: 'JPEG Compression'
        };
        console.log('JPEG file info:', fileInfo);  // Логирование для отладки
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов PNG
function handlePNG(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = new Uint8Array(event.target.result);
        const png = new pngjs();
        png.parse(data, function(error, pngData) {
            if (error) {
                console.log('Error parsing PNG:', error);
                return;
            }

            // Проверка на наличие данных о разрешении (dpi)
            let resolution = 'N/A';
            if (pngData.pHYs) {
                const dpiX = pngData.pHYs.ppuX / 39.3701; // конвертация из пикселей на метр в DPI
                const dpiY = pngData.pHYs.ppuY / 39.3701;
                resolution = `${Math.round(dpiX)}x${Math.round(dpiY)} dpi`;
            }

            const fileInfo = {
                name: fileName,
                dimensions: `${pngData.width}x${pngData.height}`,
                resolution: resolution,
                colorDepth: pngData.depth * pngData.channels,
                compression: 'Deflate (PNG)'
            };
            console.log('PNG file info:', fileInfo);  // Логирование для отладки
            addRowToTable(fileInfo);
        });
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов GIF
function handleGIF(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = event.target.result;
        const gif = require('omggif');
        const parser = new gif.GifReader(new Uint8Array(data));
        const fileInfo = {
            name: fileName,
            dimensions: `${parser.width}x${parser.height}`,
            resolution: 'N/A', // GIF не содержит DPI
            colorDepth: '8-bit (GIF)', // 8-битная палитра
            compression: 'LZW Compression (GIF)'
        };
        console.log('GIF file info:', fileInfo);  // Логирование для отладки
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов BMP
function handleBMP(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = event.target.result;
        const bmpData = bmp.decode(new Uint8Array(data));

        const fileInfo = {
            name: fileName,
            dimensions: `${bmpData.width}x${bmpData.height}`,
            resolution: 'N/A', // BMP обычно не содержит DPI
            colorDepth: bmpData.bitPP, // Глубина цвета в битах на пиксель
            compression: 'None (BMP)'
        };
        console.log('BMP file info:', fileInfo);  // Логирование для отладки
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}

// Обработка файлов TIFF
function handleTIFF(file, fileName) {
    const reader = new FileReader();
    reader.onload = function(event) {
        const data = new Uint8Array(event.target.result);
        const tiffData = tiff.decode(data);
        const firstPage = tiffData[0]; // Первое изображение в TIFF (многослойные файлы)
        const width = firstPage.width;
        const height = firstPage.height;

        // Проверка на наличие разрешения
        let resolution = 'N/A';
        if (firstPage.XResolution && firstPage.YResolution) {
            resolution = `${firstPage.XResolution}x${firstPage.YResolution} dpi`;
        }

        const fileInfo = {
            name: fileName,
            dimensions: `${width}x${height}`,
            resolution: resolution,
            colorDepth: firstPage.bitsPerSample[0], // Глубина цвета (на канал)
            compression: 'TIFF Compression (LZW/None, etc.)'
        };
        console.log('TIFF file info:', fileInfo);  // Логирование для отладки
        addRowToTable(fileInfo);
    };
    reader.readAsArrayBuffer(file);
}
