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
 * TelephoneStation - функциональный React компонент для поиска сервисов телефонной станции.
 * Модель данных доступна через window.lab1models.telephoneStationModel().
 */
const TelephoneStation = () => {
  const [searchSubstring, setSearchSubstring] = useState("");
  const [filteredServices, setFilteredServices] = useState([]);
  const [allServices, setAllServices] = useState([]);

  // Загружаем все сервисы при монтировании компонента
  useEffect(() => {
    const services = window.lab1models.telephoneStationModel();
    setAllServices(services);
    setFilteredServices(services);
  }, []);

  // Фильтруем сервисы при изменении поисковой строки
  useEffect(() => {
    if (!searchSubstring.trim()) {
      setFilteredServices(allServices);
    } else {
      const filtered = allServices.filter(service =>
        service.toLowerCase().includes(searchSubstring.toLowerCase())
      );
      setFilteredServices(filtered);
    }
  }, [searchSubstring, allServices]);

  const handleSearchChange = (event) => {
    setSearchSubstring(event.target.value);
  };

  return (
    <Box className="telephone-station-container" sx={{ p: 3, maxWidth: 800, mx: 'auto' }}>
      <Typography variant="h4" component="h1" gutterBottom>
        Телефонная станция
      </Typography>
      
      <Typography variant="h6" component="h2" gutterBottom>
        Список доступных сервисов
      </Typography>

      {/* Отображение текущей поисковой строки */}
      <Paper elevation={2} sx={{ p: 2, mb: 2, bgcolor: 'primary.light', color: 'white' }}>
        <Typography variant="body1">
          <strong>Текущий поиск:</strong> {searchSubstring || "Все сервисы"}
        </Typography>
      </Paper>

      {/* Поле ввода для поиска */}
      <TextField
        fullWidth
        label="Введите подстроку для поиска сервисов"
        variant="outlined"
        value={searchSubstring}
        onChange={handleSearchChange}
        sx={{ mb: 3 }}
        placeholder="Например: поддержка, связь, почта..."
      />

      {/* Результаты поиска */}
      {filteredServices.length === 0 ? (
        <Alert severity="info" sx={{ mb: 2 }}>
          Сервисы, содержащие подстроку "{searchSubstring}", не найдены.
        </Alert>
      ) : (
        <Typography variant="body2" sx={{ mb: 2, color: 'text.secondary' }}>
          Найдено сервисов: {filteredServices.length}
        </Typography>
      )}

      {/* Список сервисов с использованием Material UI List */}
      <Paper elevation={1}>
        <List>
          {filteredServices.map((service, index) => (
            <ListItem key={index} divider>
              <ListItemText 
                primary={service}
                primaryTypographyProps={{ variant: 'body1' }}
              />
            </ListItem>
          ))}
        </List>
      </Paper>
    </Box>
  );
};

export default TelephoneStation;
