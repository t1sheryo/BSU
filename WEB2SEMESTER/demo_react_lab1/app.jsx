import React from "react";
import ReactDOM from "react-dom";
import { HashRouter, Switch, Route, NavLink } from "react-router-dom";
import { AppBar, Toolbar, Typography, Grid, Box, List, ListItem, ListItemText, Paper } from "@mui/material";

import Example from "./components/Example";
import Regions from "./components/Regions";
import TelephoneStation from "./components/TelephoneStation";

const LinkItem = ({ to, label, exact }) => (
  <ListItem
    button
    component={NavLink}
    to={to}
    exact={exact}
    activeStyle={{ backgroundColor: "rgba(25, 118, 210, 0.08)" }}
  >
    <ListItemText primary={label} />
  </ListItem>
);

const AppLayout = () => {
  return (
    <HashRouter>
      <Box sx={{ flexGrow: 1 }}>
        <AppBar position="static">
          <Toolbar>
            <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
              Лабораторная №1 — SPA (Example, Regions)
            </Typography>
          </Toolbar>
        </AppBar>

        <Grid container spacing={2} sx={{ p: 2 }}>
          <Grid item xs={12} md={3} lg={2}>
            <Paper elevation={1}>
              <List>
                <LinkItem to="/example" label="Example" exact={true} />
                <LinkItem to="/regions" label="Regions" />
                <LinkItem to="/telephone" label="TelephoneStation" />
              </List>
            </Paper>
          </Grid>
          <Grid item xs={12} md={9} lg={10}>
            <Paper elevation={1} sx={{ p: 2, minHeight: 400 }}>
              <Switch>
                <Route exact path="/" component={Example} />
                <Route path="/example" component={Example} />
                <Route path="/regions" component={Regions} />
                <Route path="/telephone" component={TelephoneStation} />
              </Switch>
            </Paper>
          </Grid>
        </Grid>
      </Box>
    </HashRouter>
  );
};

ReactDOM.render(<AppLayout />, document.getElementById("reactapp"));


