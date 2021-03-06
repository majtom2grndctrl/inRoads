<?php
/**
 * @copyright 2014-2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Event $this->event
 * @param string $this->link Specifies what to draw a link around.
 */
use Application\Models\Event;
use Application\Models\EventType;
use Blossom\Classes\View;

$title = $this->event->getTitle()
    ? self::escape($this->event->getTitle())
    : self::escape($this->event->getGeography_description());

$id = $this->event->getId()
    ? $this->event->getId()
    : $this->event->getGoogle_event_id();

if ($this->link && $this->link === 'title') {
    $url = BASE_URI."/events/view?id=$id";
    $title = "<a href=\"$url\">$title</a>";
}

$typeClass = '';
$t = $this->event->getEventType();
if ($t) {
    $tn = View::escape($t->getName());
    $td = View::escape($t->getDescription());
    $typeDiv   = "<div class=\"type\">$tn; $td</div>";
    $typeClass = "class=\"{$t->getCode()}\"";
}
?>
<article id="e_<?= $id; ?>" <?= $typeClass; ?>>
    <h2 class="title"><?= $title; ?></h2>
    <div class="dates"><?= $this->event->getHumanReadableDuration('F j, Y'); ?></div>
    <?php

        $description = View::escape($this->event->getDescription());
        if ($description) {
            echo "\t<div class=\"description\">$description</div>\n";
        }

        $geography = $this->event->getGeography();
        echo "\t<div class=\"geography\">$geography</div>\n";
    ?>
</article>
