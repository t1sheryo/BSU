import React, { useState, useEffect } from "react";
import { 
  List, 
  ListItem, 
  ListItemText, 
  TextField, 
  Typography, 
  Box,
  Paper,
  Alert
} from "@mui/material";
import "./styles.css";

/**
 * Regions - функциональный React компонент для поиска областей Беларуси.
 * Модель данных доступна через window.lab1models.regionsModel().
 */
const Regions = () => {
  const [searchSubstring, setSearchSubstring] = useState("");
  const [filteredRegions, setFilteredRegions] = useState([]);
  const [allRegions, setAllRegions] = useState([]);

  // Загружаем все области при монтировании компонента
  useEffect(() => {
    const regions = window.lab1models.regionsModel();
    setAllRegions(regions);
    setFilteredRegions(regions);
  }, []);

  // Фильтруем области при изменении поисковой строки
  useEffect(() => {
    if (!searchSubstring.trim()) {
      setFilteredRegions(allRegions);
    } else {
      const filtered = allRegions.filter(region =>
        region.toLowerCase().includes(searchSubstring.toLowerCase())
      );
      setFilteredRegions(filtered);
    }
  }, [searchSubstring, allRegions]);

  const handleSearchChange = (event) => {
    setSearchSubstring(event.target.value);
  };

  return (
    <Box className="regions-container" sx={{ p: 3, maxWidth: 800, mx: 'auto' }}>
      <Typography variant="h4" component="h1" gutterBottom>
        Области Беларуси и г. Минск
      </Typography>
      
      <Typography variant="h6" component="h2" gutterBottom>
        Поиск по подстроке
      </Typography>

      {/* Отображение текущей поисковой строки */}
      <Paper elevation={2} sx={{ p: 2, mb: 2, bgcolor: 'primary.light', color: 'white' }}>
        <Typography variant="body1">
          <strong>Текущий поиск:</strong> {searchSubstring || "Все области"}
        </Typography>
      </Paper>

      {/* Поле ввода для поиска */}
      <TextField
        fullWidth
        label="Введите подстроку для поиска областей"
        variant="outlined"
        value={searchSubstring}
        onChange={handleSearchChange}
        sx={{ mb: 3 }}
        placeholder="Например: нс, мин, брест..."
      />

      {/* Результаты поиска */}
      {filteredRegions.length === 0 ? (
        <Alert severity="info" sx={{ mb: 2 }}>
          Области, содержащие подстроку "{searchSubstring}", не найдены.
        </Alert>
      ) : (
        <Typography variant="body2" sx={{ mb: 2, color: 'text.secondary' }}>
          Найдено областей: {filteredRegions.length}
        </Typography>
      )}

      {/* Список областей с использованием Material UI List */}
      <Paper elevation={1}>
        <List>
          {filteredRegions.map((region, index) => (
            <ListItem key={index} divider>
              <ListItemText 
                primary={region}
                primaryTypographyProps={{ variant: 'body1' }}
              />
            </ListItem>
          ))}
        </List>
      </Paper>
    </Box>
  );
};

export default Regions;
