const colorPicker = document.getElementById('colorPicker');
const colorDisplay = document.getElementById('colorDisplay');
const rgbValue = document.getElementById('rgbValue');
const hlsValue = document.getElementById('hlsValue');
const labValue = document.getElementById('labValue');

function updateColorDisplay(color) {
  colorDisplay.style.backgroundColor = color;

  const rgb = hexToRgb(color);
  //rgbValue.textContent = `rgb(${rgb.r}, ${rgb.g}, ${rgb.b})`;

  const hls = rgbToHls(rgb.r, rgb.g, rgb.b);
  hlsValue.textContent = `hls(${Math.round(hls.h)}, ${Math.round(hls.s)}%, ${Math.round(hls.l)}%)`;

  //const [l, a, b] = rgbToLab(rgb.r, rgb.g, rgb.b);
  //labValue.textContent = `lab(${Math.round(l)}, ${Math.round(a)}%, ${Math.round(b)}%)`;
}

// function labToXyz(l, a, b) {
//   const y = (l + 16) / 116;
//   const x = a / 500 + y;
//   const z = y - b / 200;

//   const y3 = Math.pow(y, 3);
//   const x3 = Math.pow(x, 3);
//   const z3 = Math.pow(z, 3);

//   const X = (x3 > 0.008856 ? x3 : (x - 16 / 116) / 7.787) * 95.047;
//   const Y = (y3 > 0.008856 ? y3 : (y - 16 / 116) / 7.787) * 100.000;
//   const Z = (z3 > 0.008856 ? z3 : (z - 16 / 116) / 7.787) * 108.883;

//   return [X, Y, Z];
// }

// function rgbToXyz(r, g, b) {
//   // Преобразование RGB в диапазоне [0, 1]
//   r = r / 255;
//   g = g / 255;
//   b = b / 255;

//   // Применение коррекции гаммы
//   r = r > 0.04045 ? Math.pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
//   g = g > 0.04045 ? Math.pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
//   b = b > 0.04045 ? Math.pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

//   // Преобразование в XYZ
//   let x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
//   let y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
//   let z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

//   return [x * 100, y * 100, z * 100]; // Умножение на 100 для результата в XYZ
// }

// function xyzToLab(x, y, z) {
//   // Опорные значения для белого
//   const refX = 95.047;
//   const refY = 100.000;
//   const refZ = 108.883;

//   x /= refX;
//   y /= refY;
//   z /= refZ;

//   x = x > 0.008856 ? Math.cbrt(x) : (7.787 * x) + (16 / 116);
//   y = y > 0.008856 ? Math.cbrt(y) : (7.787 * y) + (16 / 116);
//   z = z > 0.008856 ? Math.cbrt(z) : (7.787 * z) + (16 / 116);

//   const l = (116 * y) - 16;
//   const a = 500 * (x - y);
//   const b = 200 * (y - z);

//   return [l, a, b];
// }

// function rgbToLab(r, g, b) {
//   const [x, y, z] = rgbToXyz(r, g, b);
//   return xyzToLab(x, y, z);
// }

// function rgbToLab(r, g, b) {
//   r /= 255;
//   g /= 255;
//   b /= 255;

//   r = r > 0.04045 ? Math.pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
//   g = g > 0.04045 ? Math.pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
//   b = b > 0.04045 ? Math.pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

//   r *= 100;
//   g *= 100;
//   b *= 100;

//   let x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
//   let y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
//   let z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

//   x /= 95.047;
//   y /= 100.000;
//   z /= 108.883;

//   x = x > 0.008856 ? Math.pow(x, 1/3) : (7.787 * x) + (16 / 116);
//   y = y > 0.008856 ? Math.pow(y, 1/3) : (7.787 * y) + (16 / 116);
//   z = z > 0.008856 ? Math.pow(z, 1/3) : (7.787 * z) + (16 / 116);

//   let l = (116 * y) - 16;
//   let a = 500 * (x - y);
//   let b = 200 * (y - z);

//   return { l, a, b };
// }

// function rgbToLab(r, g, b) {
//   // Normalize RGB values to [0, 1]
//   r /= 255;
//   g /= 255;
//   b /= 255;

//   // Convert to XYZ
//   r = r > 0.04045 ? Math.pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
//   g = g > 0.04045 ? Math.pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
//   b = b > 0.04045 ? Math.pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

//   r *= 100;
//   g *= 100;
//   b *= 100;

//   // Observer = 2°, Illuminant = D65
//   let x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
//   let y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
//   let z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;

//   // Convert to LAB
//   x /= 95.047;
//   y /= 100.000;
//   z /= 108.883;

//   x = x > 0.008856 ? Math.pow(x, 1/3) : (7.787 * x) + (16 / 116);
//   y = y > 0.008856 ? Math.pow(y, 1/3) : (7.787 * y) + (16 / 116);
//   z = z > 0.008856 ? Math.pow(z, 1/3) : (7.787 * z) + (16 / 116);

//   let L = (116 * y) - 16;
//   let A = 500 * (x - y);
//   let B = 200 * (y - z);

//   // Scale L to [0, 100]
//   L = L * 100 / 100;

//   // Scale A and B to [-128, 127]
//   A = A * 255 / 354 - 128;
//   B = B * 255 / 262 - 128;

//   return { L, A, B };
// }


// function labToRgb(l, a, b) {
//   // Convert LAB to XYZ
//   let y = (l + 16) / 116;
//   let x = a / 500 + y;
//   let z = y - b / 200;

//   let y3 = Math.pow(y, 3);
//   let x3 = Math.pow(x, 3);
//   let z3 = Math.pow(z, 3);

//   y = y3 > 0.008856 ? y3 : (y - 16 / 116) / 7.787;
//   x = x3 > 0.008856 ? x3 : (x - 16 / 116) / 7.787;
//   z = z3 > 0.008856 ? z3 : (z - 16 / 116) / 7.787;

//   x *= 95.047;
//   y *= 100.000;
//   z *= 108.883;

//   // Convert XYZ to RGB
//   x /= 100;
//   y /= 100;
//   z /= 100;

//   let R = x * 3.2406 + y * -1.5372 + z * -0.4986;
//   let G = x * -0.9689 + y * 1.8758 + z * 0.0415;
//   let B = x * 0.0557 + y * -0.2040 + z * 1.0570;

//   R = R > 0.0031308 ? 1.055 * Math.pow(R, 1 / 2.4) - 0.055 : 12.92 * R;
//   G = G > 0.0031308 ? 1.055 * Math.pow(G, 1 / 2.4) - 0.055 : 12.92 * G;
//   B = B > 0.0031308 ? 1.055 * Math.pow(B, 1 / 2.4) - 0.055 : 12.92 * B;

//   R = Math.min(Math.max(0, R), 1);
//   G = Math.min(Math.max(0, G), 1);
//   B = Math.min(Math.max(0, B), 1);

//   return {
//       R: Math.round(R * 255),
//       G: Math.round(G * 255),
//       B: Math.round(B * 255)
//   };
// }

function hexToRgb(hex) {
  const bigint = parseInt(hex.slice(1), 16);
  const r = (bigint >> 16) & 255;
  const g = (bigint >> 8) & 255;
  const b = bigint & 255;
  return { r, g, b };
}

function rgbToHls(r, g, b) {
  r /= 255;
  g /= 255;
  b /= 255;
  
  const max = Math.max(r, g, b);
  const min = Math.min(r, g, b);
  let h, s, l = (max + min) / 2;

  if (max === min) {
    h = s = 0; // ахроматический цвет
  } else {
    const d = max - min;
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
    
    switch (max) {
      case r: h = (g - b) / d + (g < b ? 6 : 0); break;
      case g: h = (b - r) / d + 2; break;
      case b: h = (r - g) / d + 4; break;
    }
    
    h /= 6;
  }

  return {
    h: h * 360,
    s: s * 100,
    l: l * 100
  };
}

// function rgbToXyz(r, g, b) {
//   r /= 255;
//   g /= 255;
//   b /= 255;

//   r = r > 0.04045 ? Math.pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
//   g = g > 0.04045 ? Math.pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
//   b = b > 0.04045 ? Math.pow((b + 0.055) / 1.055, 2.4) : b / 12.92;

//   r *= 100;
//   g *= 100;
//   b *= 100;

//   const x = r * 0.4124 + g * 0.3576 + b * 0.1805;
//   const y = r * 0.2126 + g * 0.7152 + b * 0.0722;
//   const z = r * 0.0193 + g * 0.1192 + b * 0.9505;

//   return [x, y, z];
// }

// function xyzToLab(x, y, z) {
//   const refX = 95.047;
//   const refY = 100.000;
//   const refZ = 108.883;

//   x /= refX;
//   y /= refY;
//   z /= refZ;

//   x = x > 0.008856 ? Math.pow(x, 1/3) : (7.787 * x) + (16 / 116);
//   y = y > 0.008856 ? Math.pow(y, 1/3) : (7.787 * y) + (16 / 116);
//   z = z > 0.008856 ? Math.pow(z, 1/3) : (7.787 * z) + (16 / 116);

//   const l = (116 * y) - 16;
//   const a = 500 * (x - y);
//   const b = 200 * (y - z);

//   return [l, 1.28 * a, 1.28 * b];
// }

// function rgbToLab(r, g, b) {
//   const [x, y, z] = rgbToXyz(r, g, b);
//   return xyzToLab(x, y, z);
// }

// function xyzToRgb(x, y, z) {
//   x /= 100;
//   y /= 100;
//   z /= 100;

//   let r = x * 3.2406 + y * -1.5372 + z * -0.4986;
//   let g = x * -0.9689 + y * 1.8758 + z * 0.0415;
//   let b = x * 0.0557 + y * -0.2040 + z * 1.0570;

//   r = r > 0.0031308 ? 1.055 * Math.pow(r, 1 / 2.4) - 0.055 : 12.92 * r;
//   g = g > 0.0031308 ? 1.055 * Math.pow(g, 1 / 2.4) - 0.055 : 12.92 * g;
//   b = b > 0.0031308 ? 1.055 * Math.pow(b, 1 / 2.4) - 0.055 : 12.92 * b;

//   r = Math.max(0, Math.min(255, Math.round(r * 255)));
//   g = Math.max(0, Math.min(255, Math.round(g * 255)));
//   b = Math.max(0, Math.min(255, Math.round(b * 255)));

//   return [r, g, b];
// }

function rgbToHex(r, g, b) {
  return `#${((1 << 24) | (r << 16) | (g << 8) | b).toString(16).slice(1).toUpperCase()}`;
}

function updateOutputs() {
  const l = parseFloat(document.getElementById('l').value);
  const a = parseFloat(document.getElementById('a').value);
  const b = parseFloat(document.getElementById('b').value);

  labValue.textContent = `lab(${Math.round(l)}, ${Math.round(a)}%, ${Math.round(b)}%)`;
  // const [x, y, z] = labToXyz(l, a, b);
  // const rgb = xyzToRgb(x, y, z);
  const rgb = labToRgb(l, a, b);
  rgbValue.textContent = `rgb(${rgb.R}, ${rgb.G}, ${rgb.B})`;
  const lab = rgbToLab(rgb.R, rgb.G, rgb.B);
  labValue.textContent = `lab(${Math.round(lab.L)}, ${Math.round(lab.A)}%, ${Math.round(lab.B)}%)`;
  const hexColor = rgbToHex(rgb.R, rgb.G, rgb.B);
  //rgbValue.textContent = `rgb(${R}, ${G}, ${B})`;
  //rgbValue.textContent = `rgb(${hexColor})`;
  updateColorDisplay(hexColor);
}


document.querySelectorAll('input[type="number"]').forEach(input => {
  input.addEventListener('input', updateOutputs);
});

colorPicker.addEventListener('input', (event) => {
  const color = event.target.value;
  updateColorDisplay(color);
});

updateColorDisplay(colorPicker.value);
updateOutputs();